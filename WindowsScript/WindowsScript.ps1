    # Number
	g++ -c -o Number\Number.o Number\MyNumber.cpp
	ar rvs Number\MyNumber.lib Number\Number.o
	
	# Vector
	g++ -c -DVECTOR_EXPORTS -o Vector\Vector.o -INumber\ Vector\MyVector.cpp
	g++ -shared -o Vector\MyVector.dll Vector\Vector.o Number\MyNumber.lib
	
    # Main
	g++ -o WindowsScript -INumber\ -IVector\ MyMain.cpp -L.\Number\ -L.\Vector\ -lNumber -lVector

    .\WindowsScript.exe