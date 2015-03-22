Clustering Social Networks by using Genetic Algorithms, Software Project for the Course Software Engineering Lab 2015

Folder structure:

// todo

External Dependencies:

CppUnit:
	Linux: 
		sudo apt-get install libcppunit-doc libcppunit-dev
	Windows:
		Check libreoffice branch of cppunit and compile yourself
	Mac (with homebrew):
		brew install cppunit
Boost:
	Download newest version 
	Linux:
		move it to /usr/local/boost_1_57_0
		sudo ./bootstrap.sh --prefix=/usr/local
		sudo ./b2 install 
	Windows:
		move it somewhere and set BOOST_ROOT to the root
		compile the libraries
	Mac (with homebrew):
		brew install boost

Enviroment Variables:
The following enviroment variables should be defined to ease compilation.

BOOST_ROOT - boost root directory
CPPUNIT_ROOT - cpp unit root directory

Naming for test files:
As CMAKE automates the test compilation adhere to the following rules:
Add the base name of your test class to the CMakeLists.txt file in the right location.
Now assuming the base name of your test class is Foo.
Then you need to create the files: TestFoo.cpp TestFoo.hpp TestMainFoo.cpp and put them into the test directory
If you use an IDE than you should also get a project as TestFoo


Building and testing commands:
Go into the build directory(cd build) then:
cmake ..
cmake --build .
ctest -VV 
