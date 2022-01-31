# LabOEFM

codes for group MAR12, composed of Pilosio S. (RandDouble, owner of the repo), Veneziani R., Pesce M.

---

## Millikan

Used for millikan experiment during data analisis.

How to use:

`./millikan.exe <filename>`

---

## AngleCorrect

Used during reticule diffraction for correcting angle

How to use:

`./angleCorrect.exe <first Degree> <first Prime> <second degree> <second prime>`

---

## Additional info

### Compilation Info

- To Compile all the files use:

 `make`

- To Compile only angleCorrect use:

 `make angleCorrect.exe`

- To Compile only millikan use:

`make millikan.exe`

### There is some Python code

It's use is principaly for testing, but if you want to use it you only need a Python 3.9 interpreter,
on Linux it's only necessary to type:

 `python3 <nameOfProgram>`

on Windows machine you can use WSL or alternatively use powerShell, after adding to Path Variable the location of Python Interpreter and use :

`python <nameOfProgram>`    OR  `py <nameOfProgram>`

---

### Useful stuff

With this files there are included some test file
(Note that before testing the files will be recompiled)
To Test:
    `make angle`
    `make millikan`
