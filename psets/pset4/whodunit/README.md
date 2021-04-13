# Questions

## What's `stdint.h`?

Te permite ser más especificos al realizar un software de bajo nivel y ser más especificos en los tipos de datos
al ser manipulados ya que los tipos de datos int, float, long, long long tiene definidos los bits. Con stdint.h puede
ser más especificos con esos tipos de datos definiendo un ancho fijo para tener garantizados 32 o 16 bits u otros tipos.

Algunos tienen 'width' exactos
Algunos tienen 'width' especificados
Algunos tienen 'width' para contener punteros a estructuras

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

Podemos definir el ancho de un tipo de dato entero con un límite fijo. Sin embargo los tipos de datos uint solo pueden
aceptar tipos de datos > 0. Pueden ser útiles para validar operaciones matemáticas como: areas, perímetros, etc.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

Un byte es 8 bits
Un DWORD tiene 4 bytes, solo enteros positivos
Un LONG tiene 4 bytes pero puede tener números negativos
Un WORD tiene 2 bytes pero no puede tener números negativos

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

BM es el magic number y en Hexadecimal es 0x4D42

## What's the difference between `bfSize` and `biSize`?

Primero que nada, no estan en las mismas estructuras. Por que bfSize es la propiedad de BITMAPINFOHEADER
el cual tiene información sobre el tamaño, tipo, etc del archivo DBI y
bfSize es una propiedad de BITMAPFILEHEADER según la documentación de Microsoft regresa el número de
bytes definidos por la estructura usando la información de las dimensiones y formato de color

## What does it mean if `biHeight` is negative?

Entonces significa que la BDI empieza por la parte inferior izquierda y no se lee de
izquierda a derecha sino de arriba hacia abajo

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

Es biBitCount por que identifica el número de bits por pixels por lo que
puede tener 0, 1, 4, 8, 16, 24, 32, estos números en una imagen especifican la profundidad.
Por ejemplo en Photoshop al crear un proyecto especifica la profundida que por defecto es 8

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

Por que al buscar el archivo con un puntero, puede devolver NULL si no lo encuentra, no puede ser modificado u otro motivo.

## Why is the third argument to `fread` always `1` in our code?

Quiere decir que va a leer un solo item de cada archivo, en caso de fread será el archivo que esta leyendo

## What value does line 63 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

Para que se rellene con 3 bytes ya que los BMP estan formados por 8 * 3 pixeles, números divisibles entre 4 por lo que
para evitar que se almacenen diferentes se agregan ceros de Relleno para completar la columna

## What does `fseek` do?

Mover el puntero dentro del archivo para evitar los rellenos y seguir al siguiente pixel

## What is `SEEK_CUR`?

Es una variable global que mueve el puntero a una ubicación dada, en el archivo copy.c se dirige al relleno.
