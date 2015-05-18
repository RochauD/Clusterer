# Clusterer

### Clustering Social Networks by using Genetic Algorithms, Software Project for the Course Software Engineering Lab 2015

This project was created in a short period of time and was based on an incomplete and erroneous design. Therefore it would need some refactoring but other than that it works perfectly fine.

## Folder structure:

├───bin // created by cmake
├───build
├───cmake
│   └───modules
├───doc
├───include
├───lib // created by cmake
├───src
├───test
└───testing // created by cmake

## External Dependencies:

#### CppUnit:
	Linux: 
		sudo apt-get install libcppunit-doc libcppunit-dev
	Windows:
		Check libreoffice branch of cppunit and compile yourself
	Mac (with homebrew):
		brew install cppunit
#### Boost:
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
#### QT:
	Linux:
		sudo apt-get install qt4-default libqt4-dev libqt4-core libqt4-gui
	Windows:
	- VS2012+:
		Download QT 4.8.6 source version if you want to use Visual Studio with a version newer than VS2010
		Adapt make files to reflect change
		Compile it
		Set QTDIR to the root of the qt folder
	- VS2010:
		Download the old installer and just install it normally.
		Maybe set QTDIR to the root of the qt folder
	###### Mac:
#### QWT:
	Linux:
		Goto http://qwt.sourceforge.net/ and download the version 6.1 and then follow their instructions
	Windows:
	Mac:
#### Eigen:
	Windows:
		Just download Eigen 3 from their website and place it into a folder.
		Create a new enviroment variable called EIGEN_ROOT and set its value to that path
#### Armadillo:
	Linux:
		sudo apt-get install libarmadillo-dev
	Mac:

#### Enviroment Variables:
The following enviroment variables should be defined to ease compilation.

BOOST_ROOT - boost root directory
CPPUNIT_ROOT - cpp unit root directory
EIGEN_ROOT - eigen root directory (only need for windows)

#### Naming Conventions
###### Naming for test files:
As CMAKE automates the test compilation adhere to the following rules:
Add the base name of your test class to the CMakeLists.txt file in the right location.
Now assuming the base name of your test class is Foo.
Then you need to create the files: TestFoo.cpp TestFoo.hpp TestMainFoo.cpp and put them into the test directory
If you use an IDE than you should also get a project as TestFoo

## Build

Building and testing commands:
Go into the/a build directory(mkdir build & cd build) then:
cmake ..
cmake --build .
ctest -C <config> -VV 
<config> = Debug or Release etc.

Build doxygen
Run from root:
doxygen Doxyfile
