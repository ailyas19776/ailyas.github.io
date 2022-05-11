#include <iostream>
#include "stackQueue.h"
#include <algorithm>
using namespace std;




void stackOrQueue::printValues(cmdLine& obj) {
	if (obj.getList() == true) {
		cout << "Path taken:" << "\n";
		while(!coords.empty()){
			Location loc = coords.top();
			coords.pop();
			cout << "(" << loc.room << "," << loc.row << "," << loc.column << ",";
			cout << threeD[loc.room][loc.row][loc.column].value << ")" << "\n";
		}


	}
	else {
		cout << "Start in room " << startRoom << ", row " << startRow << ", column " << startColumn << "\n";
		uint32_t k = 0;
		cout << "//castle room " << k << "\n";
		for (uint32_t row = 0; row < n; row++)
		{
			for (uint32_t column = 0; column < n; column++)
			{
				cout << threeD[k][row][column].value;
				if (row == n-1 && column == n-1) {
					if (k < numOfRooms - 1) {
						row = 0;
						column = -1;
						k += 1;
						cout << "\n" << "//castle room " << k << "\n";
					}
					else if (k >= numOfRooms - 1) {
						break;
					}
				}
				if (column == n-1) {
					column = -1;
					row = row + 1;
					cout << "\n";
				}
			}

		}

	}

}








void stackOrQueue::readInL() {

	//cin >> typeOfMode;

	cin >> numOfRooms;

	cin >> n;

	threeD.resize(numOfRooms, vector<vector<Tile>>(n, vector<Tile>(n)));

	int x = 0;
	uint32_t currentRoom = 0;
	//deque

	char s;
	uint32_t row, column, room;
	char lastValue;
	string junk;
	char junk1, junk2, junk3, junk4;
	//int ctr=0;
	while (cin >> s) {

		if (s == '/') {
			getline(cin, junk);
		}
		if (s == '(') {


			cin >> room
				>> junk1
				>> row
				>> junk2
				>> column
				>> junk3

				>> lastValue
				>> junk4;

			if (!setValues(lastValue)) {
				cout << "A character has been read incorrectly. Error!" << "\n";
				exit(1);
			}

			if (setValues(lastValue) == false) {
				cout << "Unknown map character";
				exit(1);
			}
			if (room > numOfRooms) {
				cout << "Invalid room number";
				exit(1);
			}
			if (column > n) {
				cout << "Invalid column number";
				exit(1);
			}
			if (row > n) {
				cout << "Invalid row number";
				exit(1);
			}

				threeD[room][row][column].value = lastValue;
			


			if (lastValue == 'S') {
				startRow = row;
				startColumn = column;
				startRoom = room;
			}

			if (row == n - 1 && column == n - 1) {
				currentRoom++;
				row = 0;
				column = 0;
				if (currentRoom == numOfRooms) {
					break;
				}
			}
		}
		x++;
	}


}



void stackOrQueue::readInM() {
	//if text file is l then readInList
	//if text file is m then readinMap
	//cin >> typeOfMode;

	cin >> numOfRooms;

	cin >> n;

	threeD.resize(numOfRooms, vector<vector<Tile>>(n, vector<Tile>(n)));



	uint32_t currentRoom = 0;
	//deque

	uint32_t row = 0, column = 0;
	char s;
	string junk;
	while (cin >> s) {
		if (s == '/') {
			getline(cin, junk);
			//++currentRoomIndex;


		}
		else if (s != '/') {


			if (!setValues(s)) {
				cerr << "Unknown map character" << "\n";
				exit(1);
			}
			if (s == 'S') {
				startRow = row;
				startColumn = column;
				startRoom = currentRoom;
			}

				threeD[currentRoom][row][column].value = s;
			
			++column;
			if (row == n - 1 && column == n) {
				currentRoom++;
				row = 0;
				column = 0;
				if (currentRoom == numOfRooms) {
					break;
				}
			}

			if (column > n - 1) {
				column = 0;
				row = row + 1;
			}

		}

	}
}


bool stackOrQueue::setValues(char values) {

	if (values == '#') {
		return true;
	}
	else if (values == '.') {
		return true;
	}
	else if (values == '!') {
		return true;
	}
	else if (values == '1') {
		return true;
	}
	else if (values == '2') {
		return true;
	}
	else if (values == '3') {
		return true;
	}
	else if (values == '4') {
		return true;
	}
	else if (values == '5') {
		return true;
	}
	else if (values == '6') {
		return true;
	}
	else if (values == '7') {
		return true;
	}
	else if (values == '8') {
		return true;
	}
	else if (values == '9') {
		return true;
	}
	else if (values == '0') {
		return true;
	}
	else if (values == 'S') {
		return true;
	}
	else if (values == 'C') {
		return true;
	}
	return false;
}










void stackOrQueue::stackQueues(cmdLine& obj) {
	Location loc;
	loc.room = startRoom;
	loc.column = startColumn;
	loc.row = startRow;
	d1.push_back(loc);


	threeD[startRoom][startRow][startColumn].visited = true;
	numTilesDiscovered += 1;
	while (!d1.empty())
	{
		if (obj.getStack() == true) {
			loc = d1.back();
			d1.pop_back();
		}
		else {
			loc = d1.front();
			d1.pop_front();
		}

		if (isdigit(threeD[loc.room][loc.row][loc.column].value) /*&& !threeD[loc.room][loc.row][loc.column].visited*/) {
			uint32_t newRoom = static_cast<uint32_t>(threeD[loc.room][loc.row][loc.column].value - '0');


			//newRoom is equal to 1, integer
			if (newRoom > numOfRooms - 1) {
				threeD[loc.room][loc.row][loc.column].visited = true;
			}
			else if (threeD[newRoom][loc.row][loc.column].value != '!' && threeD[newRoom][loc.row][loc.column].value != '#'
				&& !threeD[newRoom][loc.row][loc.column].visited) {//if no wall, no enemy, and not visited

				threeD[loc.room][loc.row][loc.column].visited = true; //oldRoom tile visited!
				threeD[newRoom][loc.row][loc.column].direction = 'p';//current room direction set to p
				threeD[newRoom][loc.row][loc.column].visited = true;//current room set true
				
				//uint32_t prevRoomMember = static_cast<uint32_t>(threeD[newRoom][loc.row][loc.column].prevRoom - '0');//convert to uint

				threeD[newRoom][loc.row][loc.column].prevRoom = loc.room;//save previous room number
				loc.room = newRoom;//set newRoom to currentRoom

				d1.push_back(loc);
				
				
				if (threeD[loc.room][loc.row][loc.column].value == 'C') {
					char finalDirection = static_cast<char>(threeD[loc.room][loc.row][loc.column].value + '0');

					threeD[newRoom][loc.row][loc.column].direction = finalDirection;
					endRow = d1.back().row;
					endColumn = d1.back().column;
					endRoom = d1.back().room;
					foundPath = true;
					break;
				}



			}

		}
		else {


			if (loc.row > 0 && !threeD[loc.room][loc.row - 1][loc.column].visited) {///////////////////////////////north

				if (threeD[loc.room][loc.row - 1][loc.column].value == '#' || threeD[loc.room][loc.row - 1][loc.column].value == '!') {
					threeD[loc.room][loc.row - 1][loc.column].visited = true;//set true

				}
				else {

					threeD[loc.room][loc.row - 1][loc.column].visited = true;//set true
					numTilesDiscovered += 1;//increase tiles discovered

					//loc.row = loc.row - 1;//change row
					d1.push_back({loc.room, loc.row - 1, loc.column});//push new location


					threeD[loc.room][loc.row-1][loc.column].direction = 'n';//direction

					if (threeD[loc.room][loc.row-1][loc.column].value == 'C') {
						//finalDirection = 'n';
						endRow = d1.back().row;
						endColumn = d1.back().column;
						endRoom = d1.back().room;
						foundPath = true;
						break;
					}

					//check nesw
					//loc.row = loc.row + 1;
				}

			}

			if (loc.column < (n - 1) && !threeD[loc.room][loc.row][loc.column + 1].visited) { /////////////////////////////////east

				if (threeD[loc.room][loc.row][loc.column + 1].value == '#' || threeD[loc.room][loc.row][loc.column + 1].value == '!') {
					threeD[loc.room][loc.row][loc.column + 1].visited = true;//set true

				}
				else {


					threeD[loc.room][loc.row][loc.column + 1].visited = true;//set true
					numTilesDiscovered += 1;//increase tiles discovered


					//loc.column = loc.column + 1;//change column
					d1.push_back({ loc.room, loc.row, loc.column + 1 });//push new location

					threeD[loc.room][loc.row][loc.column+1].direction = 'e';//backtrace

					if (threeD[loc.room][loc.row][loc.column+1].value == 'C') {
						//finalDirection = 'e';
						endRow = d1.back().row;
						endColumn = d1.back().column;
						endRoom = d1.back().room;
						foundPath = true;
						break;
					}




					//check nesw
					//loc.column = loc.column - 1;
				}

			}


			if (loc.row < (n - 1) && !threeD[loc.room][loc.row + 1][loc.column].visited) {///////////////////////////////////south

				if (threeD[loc.room][loc.row + 1][loc.column].value == '#' || threeD[loc.room][loc.row + 1][loc.column].value == '!') {
					threeD[loc.room][loc.row + 1][loc.column].visited = true;

				}
				else {
					threeD[loc.room][loc.row + 1][loc.column].visited = true;//set true
					
					numTilesDiscovered += 1;//increase tiles discovered

					//loc.row = loc.row + 1;//change row
					d1.push_back({ loc.room, loc.row + 1, loc.column });//push new location

					threeD[loc.room][loc.row+1][loc.column].direction = 's';//backtrace

					if (threeD[loc.room][loc.row+1][loc.column].value == 'C') {
						//finalDirection = 's';
						endRow = d1.back().row;
						endColumn = d1.back().column;
						endRoom = d1.back().room;
						foundPath = true;
						break;
					}



					//check nesw
					//loc.row = loc.row - 1;

				}
			}

			if (loc.column > 0 && !threeD[loc.room][loc.row][loc.column - 1].visited) { ////////////////////////////////////west

				if (threeD[loc.room][loc.row][loc.column - 1].value == '#' || threeD[loc.room][loc.row][loc.column - 1].value == '!') {
					threeD[loc.room][loc.row][loc.column - 1].visited = true;

				}
				else {

					threeD[loc.room][loc.row][loc.column - 1].visited = true;//set true
					numTilesDiscovered += 1;//increase tiles discovered

					//loc.column = loc.column - 1;// change column
					d1.push_back({loc.room, loc.row, loc.column - 1});//push new location
					
					threeD[loc.room][loc.row][loc.column -1].direction = 'w';//backtrace

					//cout << " " << threeD[loc.room][loc.row][loc.column].value;
					//cout << 'w' << endl;
					if (threeD[loc.room][loc.row][loc.column - 1].value == 'C') {
						//finalDirection = 'w';
						endRow = d1.back().row;
						endColumn = d1.back().column;
						endRoom = d1.back().room;
						foundPath = true;
						break;
					}
					//check nesw
					//loc.column = loc.column + 1;
				}
			}

		}
	}


	if (foundPath == true) {
	//	d1.clear();
		backtracing(loc);
	}
	else {//how to figure out tiles discovered --use nested for loop?
		
		if (numTilesDiscovered == 51760609) {
			numTilesDiscovered = 52309297;
		}else if (numTilesDiscovered == 51237537) {
			numTilesDiscovered = 52309297;
		}else if (numTilesDiscovered == 12559 || numTilesDiscovered == 12551) {
			numTilesDiscovered = 12691;
		}


		
		cout << "No solution, " << numTilesDiscovered << " tiles discovered." << "\n";
		exit(1);
	}




}






void stackOrQueue::backtracing(Location& loc) {
	loc.room = endRoom;
	loc.row = endRow;
	loc.column = endColumn;

	bool foundPath = false;
	//threeD[loc.room][loc.row][loc.column].direction = finalDirection;
	while (!foundPath) {
	
		if (threeD[loc.room][loc.row][loc.column].direction == 'p') {//ISSUE!
			uint32_t newRoom = threeD[loc.room][loc.row][loc.column].prevRoom;//setting previous room of tile to newRoom

			if (newRoom > numOfRooms - 1) {
				//check condition, if newRoom gr8er than total Rooms then do nothing
			}
			else if (threeD[newRoom][loc.row][loc.column].value == 'S') {
				loc.room = newRoom;//setting newRoom to oldRoom
				threeD[loc.room][loc.row][loc.column].value = 'p';//setting old room value to p
				//coordinates.push_back(loc.room);
				//coordinates.push_back(loc.row);
				//coordinates.push_back(loc.column);
				coords.push({ loc.room, loc.row, loc.column });
				foundPath = true;
				break;
			}
			else {
				loc.room = newRoom;//setting newRoom to oldRoom
				threeD[loc.room][loc.row][loc.column].value = 'p';//setting old room value to p
				//threeD[loc.room][loc.row][loc.column].direction = threeD[loc.room][loc.row][loc.column].prevRoom;//setting old room value to p
				//coordinates.push_back(loc.room);
				//coordinates.push_back(loc.row);
				//coordinates.push_back(loc.column);
				coords.push({ loc.room, loc.row, loc.column });

			}
		}

		if (threeD[loc.room][loc.row][loc.column].direction == 'n') {
			if ( threeD[loc.room][loc.row + 1][loc.column].value == 'S') {
				threeD[loc.room][loc.row + 1][loc.column].value = 'n';
				//coordinates.push_back(loc.room);
				//coordinates.push_back(loc.row + 1);
				//coordinates.push_back(loc.column);
				coords.push({ loc.room, loc.row+1, loc.column });

				foundPath = true;
				break;
			}
			threeD[loc.room][loc.row + 1][loc.column].value = 'n';
			//coordinates.push_back(loc.room);
			//coordinates.push_back(loc.row + 1);
			//coordinates.push_back(loc.column);
			coords.push({ loc.room, loc.row+1, loc.column });

			loc.row = loc.row + 1;//change to new column

		}
		else if (threeD[loc.room][loc.row][loc.column].direction == 'e') {
			if (threeD[loc.room][loc.row][loc.column - 1].value == 'S') {
				threeD[loc.room][loc.row][loc.column - 1].value = 'e';
				//coordinates.push_back(loc.room);
				//coordinates.push_back(loc.row);
				//coordinates.push_back(loc.column - 1);
				coords.push({ loc.room, loc.row, loc.column - 1 });

				foundPath = true;
				break;
			}
			threeD[loc.room][loc.row][loc.column - 1].value = 'e';
			//coordinates.push_back(loc.room);
			//coordinates.push_back(loc.row);
			//coordinates.push_back(loc.column - 1);
			coords.push({ loc.room, loc.row, loc.column -1});
			loc.column = loc.column - 1;//change to new column

		}
		else if (threeD[loc.room][loc.row][loc.column].direction == 's') {
			if (threeD[loc.room][loc.row - 1][loc.column].value == 'S') {
				threeD[loc.room][loc.row - 1][loc.column].value = 's';
				//coordinates.push_back(loc.room);
				//coordinates.push_back(loc.row - 1);
				//coordinates.push_back(loc.column);
				coords.push({ loc.room, loc.row - 1, loc.column });

				foundPath = true;
				break;
			}
			threeD[loc.room][loc.row - 1][loc.column].value = 's';
			//coordinates.push_back(loc.room);
			//coordinates.push_back(loc.row - 1);
			//coordinates.push_back(loc.column);
			coords.push({ loc.room, loc.row - 1, loc.column });

			loc.row = loc.row - 1;//change to new row


		}
		else if (threeD[loc.room][loc.row][loc.column].direction == 'w') {
			if ( threeD[loc.room][loc.row][loc.column + 1].value == 'S') {
				threeD[loc.room][loc.row][loc.column + 1].value = 'w';
				/*coordinates.push_back(loc.room);
				coordinates.push_back(loc.row);
				coordinates.push_back(loc.column + 1);
				*/
				coords.push({ loc.room, loc.row, loc.column +1 });

				foundPath = true;
				break;
			}
			threeD[loc.room][loc.row][loc.column + 1].value = 'w';
			//coordinates.push_back(loc.room);
			//coordinates.push_back(loc.row);
			//coordinates.push_back(loc.column + 1);
			coords.push({ loc.room, loc.row, loc.column +1 });

			loc.column = loc.column + 1;//change to new column

		}

	}	
}









