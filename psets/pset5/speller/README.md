# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

Es una enfermedad causada por la intoxicación de Sílice

Also: the longest word in English.

## According to its man page, what does `getrusage` do?

Se usa para comprobar el tiempo que tarda desde que se inicia con la variable before hasta after y con
calculate regresa el tiempo total

## Per that same man page, how many members are in a variable of type `struct rusage`?

16

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

Para calcular el tiempo total de ejecución de las líneas que estan despues de before y antes de after

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

El programa necesita cargar el diccionario de palabras y su tiempo en cargarse, despues de eso hay que cargar el texto a analizar en el que
se analizara todas las letras (Los números son ignorados) buscando errores ortograficos para eso recorrer cada palabrar se guarda en 'word'
y con check ir buscando sus errores. Una vez finalizados esos proceso se procede a liberar la memoria usada. Una vez ya todo eso esta listo se muestra
el tiempo total de cada proceso en el 'main thread'.

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

Por que fcanf omite los espacios en blanco al leer el archivo también fscanf toma en cuenta los números

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

Por que son contiene palabras que no se deben modificar, ya que esas funciones usan esa variables pero no deben modificarlas

constant significa que su valor nunca cambiara.
