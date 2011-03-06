all:
	dmcs Performance.cs
	echo -e "#!/bin/bash\nmono Performance.exe" > ./performance
	chmod +x ./performance
clean:
	-rm Performance.exe ./performance result

