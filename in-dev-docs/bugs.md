
|Type| Description |
| - | - |
| Warning | |
| Error | | 
| Fixed | |

| Bug Number | Name | Description | Version Number | Fixed Status | Fix Method |
| - | - | - | - | - | - |
| 1 | Unrelated Historied Git | refusing to merge unrelated histories | 0.01 | Fixed | git pull origin dev --allow-unrelated-histories |
| 2 | no input files | Gnu make build failure | 0.02 | Fixed | The pattern rule has not recognised any object file, Continue at error 3 | Forgot to replace the example pattern substr from c to cpp |
| 3 | Cannot find |cannot find ./src/*.o, this is not a valid object file in this project,  g++ -o hello_exe ./src/main.o | 0.0.2 | Fixed | Used this pattern: $(patsubst $(sources)/%.cpp,%.o,$(wildcard $(sources)/*.cpp)), It created object files from matching all src files that match the wild card, then then replacing the prefix (directory and file name) with just the filename, and replacing .cpp with .o. Also I needed to add the objects to the recipy.
| 4 | Files did not track | The files did not get tracked by git when using -am, | 0.0.3 | Fixed | I just did git add then retried the commit