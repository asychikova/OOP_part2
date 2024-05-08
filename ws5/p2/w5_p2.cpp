#include <iomanip>
#include <fstream>
#include "Collection.h"
#include "Collection.h"     // intentional
#include "SpellChecker.h"
#include "SpellChecker.h"   // intentional
#include "Book.h"
#include "Book.h"           // intentional
#include "Movie.h"
#include "Movie.h"          // intentional

int cout = 0; // won't compile if headers don't follow convention regarding namespaces

enum AppErrors
{
    CannotOpenFile = 1, // An input file cannot be opened
    BadArgumentCount = 2, // The application didn't receive anough parameters
};

// The observer function for adding books to the collection:
//   should be called every time a new book is added to the collection
void bookAddedObserver(const seneca::Collection<seneca::Book>& theCollection,
                       const seneca::Book& theBook)
{
    std::cout << "Book \"" << theBook.title() << "\" added!\n";
}

// The observer function for adding movies to the collection:
//   should be called every time a new movie is added to the collection
void movieAddedObserver(const seneca::Collection<seneca::Movie>& theCollection,
                        const seneca::Movie& theMovie)
{
    std::cout << "Movie \"" << theMovie.title()
              << "\" added to collection \"" << theCollection.name()
              << "\" (" << theCollection.size() << " items).\n";
}

// ws books.txt movies.txt file_missing.txt file_words.txt
int main(int argc, char** argv)
{
    std::cout << "Command Line:\n";
    std::cout << "--------------------------\n";
    for (int i = 0; i < argc; i++)
        std::cout << std::setw(3) << i + 1 << ": " << argv[i] << '\n';
    std::cout << "--------------------------\n\n";

    // get the books
    seneca::Collection<seneca::Book> library("Bestsellers");
    if (argc == 5) {
      std::ifstream bookFile(argv[1]);
        if (!bookFile.is_open() ) {
            std::cout<<"ERROR: Cannot open file " <<argv[1] <<"\n";
            std::exit( AppErrors::CannotOpenFile);
        }
        
        std::string line;
        int bookCount = 0;
        while ( std::getline(bookFile,line) &&bookCount <=3) {
            if (!line.empty() &&line[0]!= '#') {
                seneca::Book newBook(line);
                library +=newBook;
                ++bookCount ;
            }
        }

        library.setObserver(bookAddedObserver);
        bookFile.close(); 
        bookFile.open(argv[1]);

        while (std::getline(bookFile,line)) {
            if (!line.empty()&& line[0]!= '#') {
                seneca::Book newBook(line);
                library +=newBook;
            }
        }
        bookFile.close();
    } 
    else 
    {
        std::cerr << "ERROR: Incorrect number of arguments.\n";
        std::exit(AppErrors::BadArgumentCount);
    }

    double usdToCadRate = 1.3;
    double gbpToCadRate = 1.5;

    auto adjustBookPrice = [ &usdToCadRate, &gbpToCadRate](seneca::Book& book) {
        if (book.country()=="US")
            book.price() *=usdToCadRate;
        else if (book.country()=="UK" &&book.year() >=1990 &&book.year()<=1999)
            book.price()*= gbpToCadRate;
    };

    std::cout << "-----------------------------------------\n";
    std::cout << "The library content\n";
    std::cout << "-----------------------------------------\n";
    std::cout << library;
    std::cout << "-----------------------------------------\n\n";

    for (size_t i = 0;i <library.size();++i)
        adjustBookPrice(library[i]);

    std::cout << "-----------------------------------------\n";
    std::cout << "The library content (updated prices)\n";
    std::cout << "-----------------------------------------\n";
    std::cout << library;
    std::cout << "-----------------------------------------\n\n";

    seneca::Collection<seneca::Movie> theCollection("Action Movies");

    // Process the file
    seneca::Movie movies[5];
    if (argc > 2) {
        std::ifstream movieFile(argv[2]);
        if (!movieFile.is_open()){
            std::cout<<"ERROR: Cannot open file "<< argv[2]<<"\n";
            std::exit(AppErrors::CannotOpenFile);
        }

		std::string line;
		int movieCount =0; 
		while (std::getline( movieFile,line) &&movieCount< 5) {
			if (!line.empty() &&line[0]!= '#') {
				seneca::Movie newMovie(line);
				movies[movieCount]=newMovie; 
				++movieCount; 
			}
		}
        movieFile.close();
    }

    std::cout << "-----------------------------------------\n";
    std::cout << "Testing addition and callback function\n";
    std::cout << "-----------------------------------------\n";
    if (argc > 2) {
        // Add a few movies to collection; no observer is set
        ((theCollection += movies[0]) += movies[1]) += movies[2];
        theCollection += movies[1];
        // add more movies; now we get a callback from the collection
        theCollection.setObserver(movieAddedObserver);
        theCollection += movies[3];
        theCollection += movies[3];
        theCollection += movies[4];
    }
    else {
        std::cout << "** No movies in the Collection\n";
    }
    std::cout << "-----------------------------------------\n\n";

    std::cout << "-----------------------------------------\n";
    std::cout << "Testing exceptions and operator[]\n";
    std::cout << "-----------------------------------------\n";

    try {
        for (auto i = 0u; i < 10; ++i)
            std::cout << theCollection[i];
    } catch (const std::exception& e) {
    std::cout << "** EXCEPTION: " << e.what() << std::endl;
}


    std::cout << "-----------------------------------------\n\n";


    std::cout << "-----------------------------------------\n";
    std::cout << "Testing the functor\n";
    std::cout << "-----------------------------------------\n";
	for (auto i = 3; i < argc; ++i)
	{
		try {
			seneca::SpellChecker sp(argv[i]);
			for (auto j = 0u; j < library.size(); ++j)
				library[j].fixSpelling(sp);
				 std::cout << "Spellchecker Statistics\n";
			sp.showStatistics(std::cout);

			for (auto j = 0u; j < theCollection.size(); ++j)
				theCollection[j].fixSpelling(sp);
				   std::cout << "Spellchecker Statistics\n";
			sp.showStatistics(std::cout);
		}catch(const char* e){
			std::cout<< "** EXCEPTION: "<< e<< "\n";
		}
			
	}
	if (argc < 3) {
		std::cout << "** Spellchecker is empty\n";
		std::cout << "-----------------------------------------\n";
	}
	std::cout << "\n";


    std::cout << "=========================================\n";
    std::cout << "Wrapping up this workshop\n";
    std::cout << "--------------- Movies ------------------\n";
    std::cout << theCollection;
    std::cout << "--------------- Books -------------------\n";
    std::cout << library;
    std::cout << "-----------------------------------------\n";
    std::cout << "Testing operator[] (the other overload)\n";
    std::cout << "-----------------------------------------\n";
    const seneca::Movie* aMovie = theCollection["Terminator 2"];
    if (aMovie == nullptr)
        std::cout << "** Movie Terminator 2 not in collection.\n";
    aMovie = theCollection["Dark Phoenix"];
    if (aMovie != nullptr)
        std::cout << "In this collection:\n" << *aMovie;
    std::cout << "-----------------------------------------\n";

    return cout;
}
