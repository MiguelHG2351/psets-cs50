from cs50 import SQL
from flask import Flask, flash, redirect, url_for, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup

# Configure application
app = Flask(__name__)


def usd(value):
    """Formats value as USD."""
    return f"${value:,.2f}"

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # selecciona los campos symbol, shares de portafolio donde el user_id sea el id que se pasa de session['user_id']
    pf = db.execute("SELECT symbol, shares FROM portfolio WHERE user_id=:id", id=session["user_id"])
    stonks = 0
    for p in pf:
        symbol = p["symbol"]
        shares = p["shares"]
        price = lookup(symbol)['price']
        total = price * shares
        stonks += total
        db.execute("update portfolio set price = :pr, total = :t where symbol = :sym and user_id = :id", pr=price, t=total, sym=symbol, id=session["user_id"])

    u = db.execute("select cash from users where id=:id", id=session["user_id"])

    cash = u[0]["cash"]

    stonks += cash

    npf = db.execute("select * from portfolio where user_id = :id", id=session["user_id"])

    transactions = db.execute(
        "SELECT symbol,SUM(share) as shares, price_per_share as price,SUM(TOTAL) as total  FROM transactions WHERE user_id = :id GROUP BY symbol, price_per_share", id=session["user_id"])

    return render_template("index.html", cash=usd(cash), stonks=usd(stonks), transactions=transactions, usd = usd)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        quote = lookup(request.form.get("symbol"))
        print(quote)
        if quote == None:
            return apology("Simbolo invalido", 400)

        # si es entero positivo
        try:
            share = int(request.form.get("shares"))
        except:
            return apology("Las acciones deben ser positivas", 400)

        # Si no especifico la cantidad de acciones  a comprar
        if share <= 0:
            return apology("Debes solicitar un numero de acciones")

        # consulta la base de datos para el username, 'selecciona el cash de la tabla users donde el id sea: '
        rows = db.execute("SELECT cash FROM users  WHERE id = :user_id", user_id=session["user_id"])

        # dinero que el usuario dispone en la cuenta y el que va a gastar en share
        cash_remaining = rows[0]["cash"]
        price_per_share = quote["price"]

        # calcula el precio de las acciones solicitadas
        total_price = price_per_share * share

        if total_price > cash_remaining:
            return apology("No posee fondos suficientes para completar esta accion")

        # Actualiza estas tablas con estos valores, y donde el id sea: . E inserta en el historial de transacciones estos valores
        db.execute("UPDATE users SET cash = cash- :price WHERE id = :user_id", price=total_price, user_id=session["user_id"])
        db.execute("INSERT INTO  transactions (user_id, symbol, share, price_per_share, TOTAL) VALUES (:user_id, :symbol, :share, :price, :total)",
                    user_id=session["user_id"],
                symbol=request.form.get("symbol"),
                share=share,
                price=price_per_share, total=total_price)
        flash("Bought!") # Mensaje de todo bien, todo correcto

        return redirect(url_for("index"))
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute("SELECT symbol, share, price_per_share, date FROM transactions WHERE user_id = :user_id ORDER BY date",
                            user_id=session["user_id"])

    return render_template("history.html", transactions=transactions, usd=usd)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        user = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(user) != 1 or not check_password_hash(user[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = user[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("insert symbol")

        q = lookup(request.form.get("symbol"))

        if not q:
            return apology("simbolo invalido")
        else:
            return render_template("quoted.html", symbol=q["symbol"], price=q["price"])
    else:
        return render_template("quote.html")



@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get('username')
        password = request.form.get('password')
        confirmation = request.form.get('confirmation')

        if not username:
            return apology("No ingreso el usuario, por favor ingreselo para crear su cuenta c:")
        if not password:
            return apology("La contraseña es importante, agregue una segura")
        if password != confirmation:
            return apology("Parece que escribiste mal un caracter o número, F")
        if db.execute("SELECT username FROM users WHERE username = :username", username=request.form["username"]):
            return apology("El nombre de usuario ya existe, intenta con otro")
        userID = db.execute('INSERT INTO users(username, hash) VALUES (:username, :pwd)', username = username, pwd=generate_password_hash(password))
        session['user_id'] = userID

        return redirect('/')

    elif(request.method == "GET"):
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == 'POST':
        if not request.form.get("symbol"):
            if not request.form.get('symbol'):
                return apology("No es una acción valida", 400)
        quote = lookup(request.form.get("symbol"))
        if quote == None:
            return apology('Invalid symbol', 400)

        if not request.form.get("shares").isnumeric() or int(request.form.get("shares")) < 1:
            return apology("Accion incorrecta", 400)
        try:
            share = int(request.form.get("shares"))
        except:
            return apology("Las acciones deben ser positivas", 400)

        if share <= 0:
            return apology("Debes solicitar un numero de acciones", 400)

        users = db.execute("SELECT cash FROM users  WHERE id = :user_id", user_id=session["user_id"])
        shares = int(db.execute('SELECT share FROM transactions WHERE user_id=:id', id=session['user_id'])[0]['share'])

        current_cash = users[0]["cash"]
        price_per_share = quote["price"]
        total_price = price_per_share * share
        print(f'shares: ${shares}, share: ${share}')
        if total_price > current_cash:
            return apology("No posee fondos suficientes para completar esta accion", 403)
        if share > shares:
            return apology("Too many symbols", 400);

        db.execute("UPDATE users SET cash = cash + :price_per_share WHERE id = :user_id",
                    price_per_share=total_price, user_id=session["user_id"])

        db.execute("INSERT INTO  transactions (user_id, symbol, share, price_per_share, TOTAL) VALUES (:user_id, :symbol, :share, :price, :TOTAL)",
                    user_id=session["user_id"],
                    symbol=request.form.get("symbol"),
                    share=share*-1,
                    price=price_per_share,
                    TOTAL=price_per_share*share*-1)
        flash("Sold!")

        return redirect("/")

    else:
        stocks = db.execute("SELECT symbol, SUM(share) as total_share FROM transactions WHERE user_id= :user_id GROUP BY symbol HAVING total_share > 0",
                            user_id=session["user_id"])
        return render_template("sell.html", stocks=stocks)

def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
