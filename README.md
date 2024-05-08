# OOP_part2
/*
*****************************************************************************
                          OOP345 Project
Full Name  : Anna Sychikova
Student ID#: 159363217
Email      : asychikova@myseneca.ca
Section    : NAA
Date of completion: 5th of April, 
I started Project at the first day of the release, during the midterm week, ~26 of February
*****************************************************************************
*/

In this project we have: 

Orders: customer order associated with a name of a person and set of items, all items should be filled (if number of items is allows to do that).
Stations: stations where goods are stored, filling order if it's order require that item and if it is in stock.
Workstation: manages three queues of CustomerOrders: g_pending, g_completed, and g_incomplete. Each queue holds orders at different stages:
    g_pending: orders that waiting for placing in the assembly line on first station.
    g_completed: orders that have been removed from last station and completely filled.
    g_incomplete: orders that have been removed from last station but could not be filled completely.
orders from the deque of customer orders m_orders within each Workstation will be sent to one of global queues (g_pending, g_completed, g_incomplete).Workstation object is responsible for managing customer orders at a particular station on the assembly line. 
Line manager: manages an assembly line of stations, initialize assembly line, reorder stations, run operations on the workstations for a single iteration. Also it is responsible for movement of items ensuring that each order is filled (or tried to be filled)

-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
						/-----------\
						| Utilities |
						\-----------/
-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
Utilities module contains solution for parsing string data from input files into tokens. It will be used to extract all tokens from files. It have: 
size_t m_widthField =1 ; which is a length of token,
static char m_delimiter; separates tokens in string.

*****************************************************************
void Utilities::setFieldWidth(size_t newWidth) {
     m_widthField =newWidth;
} - set field width with new value of newWidth

*****************************************************************
size_t Utilities::getFieldWidth() const {
     return m_widthField;
} - return field width 

*****************************************************************
std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) { - extracts token from string 

	1.std::string token; - token will hold the extracted token,
          size_t delimiterPos =str.size(); - delimiterPos set to size of the input string, 
	  size_t startPos = 0; - startPos used for removing spaces from the start of the token
	  size_t endPos =token.length(); endPos used for removing spaces from the end of the token
	2.for (size_t i =next_pos; i<str.size();++i) {
            if (str[i] ==m_delimiter) {
                delimiterPos= i;
                break;}
        } - iterates through string starting from the position next_pos until end of string its trying to find specified m_delimiter(check if the character at current position i is equal to delimiter). When delimiter is found, delimiterPos is updated, and the loop breaks. Also it can be done with find function. 
	3. when delimiterPos is not equal to size of input string - it means a delimiter was found, and extraction of token will be started from next_pos to delimiterPos - next_pos using std::string::substr()
	4.after it checks if extracted token is empty or not. If it is empty it sets more to false - no more tokens are available, throw error.
	5.updates next_pos to the position + 1 after delimiter, more is true, more tokens can exist
	6.std::isspace() remove all spaces from start and end of the token
	7. return token 
Also function updates m_widthField with length of the extracted token if it is more than current value of m_widthField.

*****************************************************************
void Utilities::setDelimiter(char newDelimiter) {
    m_delimiter =newDelimiter;
} - set the received delimiter

*****************************************************************
char Utilities::getDelimiter() {
    return m_delimiter;
} - return delimiter 


-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
						/-----------\
						|  Station  |
						\-----------/
-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
Station module manages station, each station created to fill specific item. It have functionality which help to identify stations from file using utilities module because station files have data separated by delimiter. Also it contains functions that allows to manage the state of station.

Class station have: 
       int m_id; - id of the station
       std::string m_itemName; - name of station
       std::string m_description ; - description of station
       unsigned int m_nextSerialNumber; - next serial number assigned to station which will be used to link one station to another(in order to create a list of linked stations)
       unsigned int m_quantity ; - number of items in stock 
       static size_t m_widthField; - max number of characters for printing item name used in display
       static size_t id_generator; - variable to hold an id 

*****************************************************************
It have constrictor: 
 Station::Station(const std::string& str) 
	1.instance of Utilities is created (Utilities util;)
	2.bool more =true;
        size_t next_pos =0; - are initialized 
 	3.item name, next serial number, and quantity extracted by Utilities::extractToken()
	4.convert extracted next serial number and quantity from strings to integer using std::stoi() (string to integer)
	5.adjust width field based on the length of item name and maximum founded field width 
	6.trim description by removing leading and trailing spaces
	7.assigns result of incremented id_generator to m_id , when new station instance is created, id_generator is incremented and this value assigned to m_id. 

*****************************************************************
const std::string& Station::getItemName() const {
     return m_itemName;
} - return name of Station

*****************************************************************
size_t Station::getNextSerialNumber() {
    return m_nextSerialNumber++;
} - return incremented next serial number 

*****************************************************************
size_t Station::getQuantity() const {
    return m_quantity;
} - return quantity that remain in stock

*****************************************************************
void Station::updateQuantity() {
    if (m_quantity> 0) {
        m_quantity--;
    }
    else {
        std::cout <<"Quantity cannot be less than 0"<< std::endl;
    }
} - subtract 1 from stock available quantity and it can't be less than 0 before subtraction

*****************************************************************
void Station::display(std::ostream& os, bool full) const {
        os << std::setw(3) <<std::setfill('0') << std::right<< m_id
           <<" | " <<std::setw(m_widthField)<<std::left <<std::setfill(' ')<<m_itemName
           << "| "<<std::setw(6) <<std::right<<std::setfill('0') <<m_nextSerialNumber<<" | ";

        if (full)
        {
            os<<std::setw(4)<< std::right <<std::setfill(' ')<< m_quantity<< " | "<<m_description;
        }
        os << std::endl;
    } - display function is used for displaying information about station. If there is a requirement to do not show full, only id, name and serial number will be displayed. If there is a true in full parameter, then quantity and description will be shown as well. Also it is formatted using m_widthField. 


-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
						/---------------\
						| CustomerOrder |
						\---------------/
-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
CustomerOrder manages single order on the assembly line

It have struct Item and 
   std::string m_name; - name of the customer
   std::string m_product; - name of the product (Bed, Desk)
   size_t m_cntItem; - count of the number of items in the customer's order
   Item** m_lstItem; - array of pointers to dynamically allocated object of Item type
   static size_t m_widthField; - used for display

*****************************************************************
It also have a default constructor: CustomerOrder::CustomerOrder() :m_name(""),m_product(""), m_cntItem(0),m_lstItem(nullptr){} which initialize object to empty state

*****************************************************************
Custom constructor which uses Utilities for extract tokens since content of the string is separated by "|", it dynamically allocate memory for array of Item pointers to store each item from customer order. CustomerOrder::CustomerOrder(const std::string& record): CustomerOrder(){

	1.instance of Utilities class named util created
	2.position and more tokens are initialized to 0 and true
	3.extractToken function from Utilities called to extract m_name and m_product from the record string.  Updates pos and more. pos will be updated to position right after name token, and after extraction of product - right after product
	4.count of items m_cntItem is 0
	5.iteration over each character in record string. If character match delimiter from Utilities object util, m_cntItem will be incremented. After loop, decrement m_cntItem by 1(to take correct number of items, since it counts all delimiters and if on the record count of delimiters is 6 then number of items will be 5).
	6.check if count of items is more than 0, and if it is then allocate memory for array of pointers to Item with size of count of items
	7.loop through all items and extract item record from record string until delimiter "|", creates Item with extracted record and store address of record in m_lstItem. pos++ is used inside the loop to make sure that character at current position is processed before moving to next position.
++pos is used after loop to move pos to position right after delimiter for next iteration
	8.after it remove spaces in Item name from start and end. 
	9.update width if it is less than utilities width

*****************************************************************
Copy constructor is not allow copy operations: 

 CustomerOrder::CustomerOrder(const CustomerOrder& src){
        throw std::string( "Copy operations are not allowed");
    }
and Copy assignment is deleted : CustomerOrder& operator=(const CustomerOrder&) = delete;

*****************************************************************
move constructor
    CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept{
        m_name =src.m_name;
        m_product= src.m_product;
        m_cntItem= src.m_cntItem;
        m_lstItem =src.m_lstItem;
        src.m_cntItem =0;
        src.m_lstItem= nullptr;
    } - designed to transfer resources from source object to new constructed object, source object is empty 


*****************************************************************
move assignment operator
    CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept {
        if (this !=&src){
            m_name =src.m_name;
            m_product= src.m_product;
            m_cntItem= src.m_cntItem;
            m_lstItem =src.m_lstItem;
            src.m_cntItem =0;
            src.m_lstItem= nullptr;

            if (src.m_lstItem) {
                for (size_t i = 0;i < src.m_cntItem; ++i) {
                    delete src.m_lstItem[i] ;
                }
            }
        }
        return *this;
    } - transfer resources from source object src to current object *this, delete used to manage dynamically allocated resources for list of items

*****************************************************************
destructor
    CustomerOrder::~CustomerOrder() {
        if (m_lstItem !=nullptr) {
            for (size_t i= 0;i < m_cntItem; ++i){
                delete m_lstItem[i];
            }
            delete[] m_lstItem;
            m_lstItem= nullptr;
        }
    } - cleaning resources for list of items of CustomerOrder instance

*****************************************************************
    bool CustomerOrder::isOrderFilled() const{
        for (size_t i =0;i < m_cntItem; ++i) {
            if (!m_lstItem[i]-> m_isFilled){
                return false;
            }
        } return true;
    } - this function return true is all items in order are filled, function go through all items in order and return false if founds unfilled item. If all items are filled, it returns true. Item filling in fillSingleItem function

*****************************************************************
 bool CustomerOrder::isItemFilled(const std::string& itemName) const {
    bool itemFound= false;
    for(size_t i=0; i <m_cntItem; ++i){
        if (m_lstItem[i]->m_itemName== itemName) {
            itemFound =true;
            if (!m_lstItem[i]-> m_isFilled) {
                return false;
            }
        }
    } if(!itemFound) {
        return true;
    }
    return true;
} - return true if all items specified by itemName!!! filled or if item doesn't exist in order, iterates through all items in order, checks specified item is found and filled, return true if the item is found and filled or if it is not found. It return false if specified item is found but not filled.

*****************************************************************
void CustomerOrder::fillItem(Station& station, std::ostream& os) { - iterates through each item in the customer order, check if item should be filled, attempt to fill it if conditions are met, and handle case where item cannot be filled due to low quantity.

    void CustomerOrder::fillItem(Station& station, std::ostream& os){
        for (size_t i =0;i < m_cntItem;++i) { - loop through each item in customer order
            if (isItemToBeFilled(station,i)) { - check if current item should be filled by station by calling function which is checks if name of item is the same as station name
                if (station.getQuantity()> 0) { - check if station has available quantity to fill the item
                    fillSingleItem(station,os, i); - fill item using station
                    break; - exit
                } else{
                    unableToFillItem(os,i); - print message
                }
            }
        }
    }

*****************************************************************
bool CustomerOrder::isItemToBeFilled(Station& station, size_t index) 
station.getItemName() == m_lstItem[index]->m_itemName: compares name of item associated with station object (got using getItemName()) to name of item stored in m_lstItem array at specified index. It checks if they are the same. If they are not same - false. !m_lstItem[index]->m_isFilled - checks if item at index in the m_lstItem array has been filled by calling m_isFilled variable of item at that index. if item is not filled - true.
station.getItemName() == m_lstItem[index]->m_itemName && !m_lstItem[index]->m_isFilled returns true if 
name of the item associated with the station matches name of item at index in customer order and item at specified index in customer order has not been filled 

*****************************************************************
    void CustomerOrder::fillSingleItem(Station& station, std::ostream& os,size_t index) { - filling a single item in a customer order
        m_lstItem[index]-> m_serialNumber =station.getNextSerialNumber(); - assign next serial number from station to m_serialNumber member variable of item at specified index in customer order
        m_lstItem[index]->m_isFilled =true; - mark item as filled
        station.updateQuantity() ; - update quantity in the station (- 1)
        os<<"    Filled "<<m_name<< ", " <<m_product <<" [" <<m_lstItem[index]-> m_itemName<< "]" <<std::endl;- otput message that item was filled
    }
*************
void CustomerOrder::unableToFillItem(std::ostream& os, size_t index) { - simply prints a message that item cannot be filled
 
*************
    void CustomerOrder::display(std::ostream& os) const { - 
        os<< m_name<< " - "<<m_product <<std::endl;
        for (size_t i =0;i < m_cntItem; ++i) {
            os<<"[" <<std::setw(6) <<std::setfill('0') <<std::right<<m_lstItem[i]->m_serialNumber<< "] "
            <<std::setw(m_widthField -1) <<std::setfill(' ')<<std::left <<m_lstItem[i]->m_itemName<< "- "<<(m_lstItem[i]->m_isFilled ? "FILLED" :"TO BE FILLED") <<std::endl;
        }
    } - used for displaying orders in different states (complete and incomplete)

-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
						/-------------\
						| WorkStation |
						\-------------/
-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
WorkStation - active station on the assembly line and contains all functionality for filling customer orders with station items. Workstation derived from the Station. 
    extern std::deque<CustomerOrder> g_pending ; - hold orders that should be placed in assembly line on first station
    extern std::deque<CustomerOrder> g_completed; - hold orders that removed from last station and have been completely!!! filled
    extern std::deque<CustomerOrder> g_incomplete; - hold orders that removed from last station and could not be filled!!! completely

 std::deque<CustomerOrder> m_orders; - variable m_orders, which is a double-ended queue of CustomerOrder objects, each element in the deque represent individual order placed by a customer
 Workstation* m_pNextStation ; - next station in the assembly line where orders can move to after processing at the current workstation
constructor Workstation::Workstation(const std::string& record) initialize Workstation object by calling constructor of its base class Station. 

*****************************************************************
    void Workstation::fills(std::ostream& os){
        if (m_orders.empty()){
            return; - no orders in queue, return without doing anything
        }m_orders.front().fillItem(*this,os); - fills order called on first element of queue which is on front of queue. It gives a reference to current Workstation object (*this) which acts as a Station object since Workstation is derived from Station and reference to output stream os to fillItem function. This function fill current order at workstation.
    }

*****************************************************************
bool Workstation::attemptToMoveOrder() { - attempts to move order at the front of queue to next station in assembly line. If order can be moved, it's moved to the next station or!!! marked as completed/incomplete depending on if it is the last station in line
        if (m_orders.empty()) - if there is no orders to work with
            return false ; - returns false
        auto& thisOrder =m_orders.front(); - reference thisOrder to first CustomerOrder object in m_orders deque. now thisOrder represent a first order in deque.
        bool canMoveOrder= thisOrder.isItemFilled(getItemName())|| getQuantity() ==0; - if current item in order is filled or if there is no quantity left in current station, canMoveOrder is set to true, order can be moved (getItemName get station name and after in itemFilled it compares item with name which is same as station with name of item or not)
        if (!canMoveOrder) - order cannot be moved if item is not filled or if there is quantity in stock return false
            return false; 
        if (!m_pNextStation){ - checks if there is a next station, if not- this station is the last in assembly line 
            if(thisOrder.isOrderFilled() ) - if current order is completely filled 
                g_completed.push_back(std::move( thisOrder)); - if current order is completely filled - order is moved to g_completed queue
            else
                g_incomplete.push_back(std::move( thisOrder)); - if current order is not completely filled - moved to the g_incomplete queue.
            m_orders.pop_front() ; - current order removed from front of m_orders deque 
            return true; 
        }*m_pNextStation +=std::move( thisOrder) ; - if there is a m_pNextStation, current order is moved to that station and added to end of next station queue, using overloaded operator+= of Workstation, passing thisOrder as a parameter
        m_orders.pop_front(); 
        return true; - current order is removed from front of m_orders deque 
    }

*****************************************************************
    void Workstation::setNextStation(Workstation* station) {
        m_pNextStation = station; - m_pNextStation member variable will point to "next" station object
    }

*****************************************************************
    Workstation* Workstation::getNextStation() const {
        return m_pNextStation; - return pointer to next Workstation in assembly line and gives access to next station without modifying its value
    }
*****************************************************************
    void Workstation::display(std::ostream& os) const {
        os<<getItemName()<< " --> " << (m_pNextStation? m_pNextStation-> getItemName() :"End of Line")<< std::endl;
    } - insert information about current Workstation

*****************************************************************
    Workstation& Workstation::operator+=(CustomerOrder&& custOrder) {
        m_orders.push_back(std::move( custOrder)); - move custOrder object into m_orders deque of current Workstation object, and add new order to end of queue.
        return *this; - return reference to current Workstation after adding new order
    } - when *m_pNextStation += std::move(thisOrder) is called it use operator+= of next workstation *m_pNextStation. custOrder - result of moving thisOrder, is added to m_orders deque of next workstation using m_orders.push_back(std::move(custOrder)); it transfers order from current workstation to next

-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
						/-------------\
						| LineManager |
						\-------------/
-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
LineManager - responsible for manage flow of customer orders through assembly line of workstations
std::vector<Workstation*> m_activeLine - collection of workstations for line. It is ensuring that each order progress through workstations until it is complete or marked as incomplete
size_t m_cntCustomerOrder – total number of customer orders
Workstation* m_firstStation - points to first active station on the line

constructor LineManager(const std::string& file, const std::vector<Workstation*>& stations)
    const std::string& file: reference to name of a file, contain information about line configuration.
    const std::vector<Workstation*>& stations: reference to a vector represents all workstations in the assembly line.

*****************************************************************
LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) : m_cntCustomerOrder(0), m_firstStation(nullptr) {
        std::ifstream filename(file); - creates an input file stream filename
        std::string record; - store line readed from file
        m_cntCustomerOrder= g_pending.size(); - initialize m_cntCustomerOrder with num of elements of g_pending queue
        while (std::getline(filename, record )) { - first while loop read each line from file and based on station names extracted from file, initialize m_activeLine vector with pointers to Workstation objects 
            char delimiter ='|'; - initialize delimiter, since in AssemblyLine.txt stations separated by "|" character
            size_t delimiterPos = record.find(delimiter); - find position of first delimiter in line using find().
            std::string firststName= record.substr(0,delimiterPos); - extract substring from beginning of line until delimiter, it will be name of first station.
            for (Workstation* st :stations) { - go through vector of Workstation pointers 
                if (st->getItemName() ==firststName) { - compare name of the current Workstation with the name extracted from AssemblyLine.txt file.
                    m_firstStation = st; - if match found, assign address of matching Workstation to first station
                    break;
                }
            } if (m_firstStation) {
                m_activeLine.push_back(m_firstStation);
                } - if match Workstation found, add it to m_activeLine vector
        }
        filename.clear();
        filename.seekg(0); - reset file stream to start

        while (std::getline(filename,record)) { - read each line from file again to establish station links
            char delimiter ='|'; - initialize delimiter
            size_t delimiterPos = record.find(delimiter); - find where delimiter in current line
            if (delimiterPos !=std::string::npos){ - if delimiter is in line
                std::string firststName= record.substr(0,delimiterPos); - extract name of first station from line
                std::string secondstName =record.substr(delimiterPos +1); - and extract name of second station from line automatically extracts characters until the end of string


                Workstation* secondst =nullptr; 
                for (Workstation* st : m_activeLine) { - iterate through Workstation objects in m_activeLine
                    if ( st->getItemName() == firststName) {
                        m_firstStation = st; - search for first station in m_activeLine vector
                    }
                    if ( st->getItemName() == secondstName) {
                        secondst = st; - search for second station in m_activeLine vector
                    }
                }
                if (m_firstStation && secondst){
                m_firstStation->setNextStation(secondst); - if first and second stations found, link between them using setNextStation from WorkStation will be set
                }
            } 
without this part there was conditional jump because case when record do not contains delimiter was not handled:  else {
                std::string laststName= record ; - if no delimiter found thats mean that this is last station, initialize with name of last station 
                Workstation* lastst = nullptr; - pointer lastst to a Workstation object
                for (Workstation* st : m_activeLine) { - iterate through Workstation objects in m_activeLine
                    if ( st->getItemName() ==laststName) { - if name of current Workstation match name extracted from file
                        lastst= st;
                        break; - match is found, assign address of matching Workstation to lastst and exit
                    }
                } 
                if( lastst) {
                lastst->setNextStation(nullptr );
                } - lastst is not nullptr, it means a matching Workstation was found. Set next station of lastst to nullptr, thats mean the end of line
            } 
        }
    }

*****************************************************************
   void LineManager::reorderStations() { - rearrange order of stations in line and try to find station on which no one point
        std::vector<Workstation*> reorderedLine; - vector reorderedLine for pointers to Workstation objects
        for (Workstation* st : m_activeLine){ - iterate through Workstation* pointers in m_activeLine vector
            bool isStartSt = true; -  boolean variable isStartSt initialized to true
            for (Workstation* otherStation : m_activeLine) { - iterate through each Workstation* pointer in m_activeLine vector again, used to find starting station
                if (otherStation->getNextStation() ==st) { - if current otherStation has current st as its next station thats mean that it is not a first station - exit 
                    isStartSt = false;
                    break;
                }
            }
            if (isStartSt){ - isStartSt is still true after previous loop, it means st is starting station, assign address of st to firstst and break big loop
                m_firstStation = st;
                break;
            }
        }
        if (!m_firstStation){
            throw std::runtime_error("Error: Unable to determine the first station to reorder.");
        } - start station was not found, so it throws a runtime 

        Workstation* currentStation = m_firstStation; - pointer to Workstation object currentStation initialize it with starting station firstst
        while (currentStation){ - loop that iterates until currentStation is not nullptr in line
            reorderedLine.push_back(currentStation) ; - add station pointed by currentStation to reorderedLine vector, in first iteration it will add firstst, in second - next station of firstst 
            currentStation =currentStation->getNextStation(); - now currentStation point to next station
        }

        if (reorderedLine.size()!= m_activeLine.size()) {
            throw std::runtime_error("Error: Unable to reorder all stations.");
        } - check if size of reorderedLine vector is not equal to size of m_activeLine vector(num of elements). if they are not equal, it means that some stations were not reordered
        m_activeLine =reorderedLine; - set m_activeLine vector with the reordered stations
        m_firstStation = m_activeLine.front(); - point to first station in reordered line
    }

*****************************************************************
  bool LineManager::run(std::ostream& os){
        static size_t iterationCount =1; - static variable iterationCount, will save value between function calls
        os<<"Line Manager Iteration: "<<iterationCount++ <<std::endl; 

        if(!g_pending.empty()){
            *m_firstStation +=std::move(g_pending.front());
            g_pending.pop_front();
        } - if g_pending queue it's not empty, move front element of g_pending queue to first station in  line (m_firstStation). it then remove front element from g_pending queue
        for(const auto& st : m_activeLine) {
            st->fills(os) ;
        } - iterate through station in m_activeLine vector and call fill of each station, fill order at station only if there are pending orders
        for (auto& st : m_activeLine) {
            st->attemptToMoveOrder();
        } - iterate over each station in m_activeLine vector and call attemptToMoveOrder of each station, attempt to move orders from each station to next station in line
        size_t totalCompletedAndIncomplete =g_completed.size() + g_incomplete.size(); - calculate total number of completed and incomplete orders by sum size of g_completed and g_incomplete queues
        return totalCompletedAndIncomplete == m_cntCustomerOrder; - if m_cntCustomerOrder and sum of orders are equal thats mean that all orders are processed - true. if not equal - false 

    }

*****************************************************************
    void LineManager::display(std::ostream& os) const { 
        for (const auto* station : m_activeLine ) - iterate through each workstation in m_activeLine
            station->display(os) ; - call display function 
    }





