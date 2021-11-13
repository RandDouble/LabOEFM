# LabOEFM
codes for grop MAR12, composed of Pilosio S. (RandDouble, owner of the repo), Veneziani R., Pesce M.
## Millikan
used for millikan experiment during data analisis
    use: ./millikan.exe <filename>
## AngleCorrect 
Used during reticule diffraction for correcting angle
    how to use:
    ./angleCorrect.exe <first Degree> <first Prime> <second degree> <second prime>
    needs improving
## Additional info
### Compilation Info
To Compile all the files use:
    make
To Compile only angleCorrect use:
    make angleCorrect.exe
To Compile only millikan use:
    make millikan.exe
### Useful stuff
With this files there are included some test file
(Note that before testing the files will be recompiled)
To Test:
    make angle
    make millikan
## To Do
    correction for e/m experiment
    correction for prism