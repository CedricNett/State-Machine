#include <iostream>
#include <string>

namespace local
{
	struct stateEngine_T
	{
	private:
		// States könnten auch einfach Nummern sein.
		// Auf diese Weise wird der Code aber ausdrücklicher
		using state_T = enum{
			panic_S,
			idle_S,
			state1_S,
			state2_S,

			state3_S,	//Neuer State

			exit_S
		};
		state_T nextState_;
		
		// Diese privaten Funktionen würden kapseln, was zu den Transitionen
		// erfüllt sein müsste.
		bool checkForProblems(int Ergebnis)		
		{ 	/*Auswertung*/ 
			if(Ergebnis==0)
			{
				return true;
			}
			else
			{
				return false;
			}
			
		};

		bool hasProcessFinished(int Ergebnis)	
		{ 	/*Auswertung*/ 
			if(Ergebnis!=0)
			{
				return true;
			}
			else
			{
				return false;
			}
		};
			

		bool evaluateTransitionGuard1(int Auswahl)	
		{	/*Auswertung*/
			if(Auswahl == 1)
			{
				return true;
			}
			else
			{
				return false;
			};
		}
		
		bool evaluateTransitionGuard2(int Auswahl)
		{	/*Auswertung*/
			if(Auswahl == 2)
			{
				return true;
			}
			else
			{
				return false;
			};
		}

		bool evaluateTransitionGuard3(int Auswahl)
		{	/*Auswertung*/
			if(Auswahl == 3)
			{
				return true;
			}
			else
			{
				return false;
			};
		}



		// Die State-Funktionen führen aus, was in dem jewiligen State passieren
		// soll. Der return-Wert ist der jeweilige nächste Zustand in den die 
		// Engine versetzt werden soll.
		// Dabei gibt es Zustände welche einfach eine Funktion ausführen und dann
		// die Engine direkt in den nächsten Zustand versetzen.
		state_T panic(){
			std::cout << "Bitte jetzt in Panik ausbrechen" << std::endl;
			//Panikaktion
			return exit_S;
		}
		
		// aber auch Zustände welche in einer Schleife verharren bis ein 
		// Transition-Guard erfüllt ist. 
		// Je nach erfülltem Transition-Guard können die folgenden States 
		// unterschiedlich sein.
		state_T runState1(){
			while(true){
				//Funktionskörper des Zustands
				int zahl1=0, zahl2=0, summe=0;

				std::cout << "Geben Sie 2 Zahlen zur addition ein:" << std::endl;
				std::cin >> zahl1;
				std::cin >> zahl2;

				summe=zahl1+zahl2;
				
				std::cout << "Ergebnis = " << summe << std::endl;

				if(checkForProblems(summe)) return panic_S;
				if(hasProcessFinished(summe)) return idle_S;
			}
		}

		state_T runState2(){
			while(true){
				int zahl1=0, zahl2=0, differenz=0;

				std::cout << "Geben Sie 2 Zahlen zur subtraktion ein:" << std::endl;
				std::cin >> zahl1;
				std::cin >> zahl2;
				
				differenz=zahl1-zahl2;

				std::cout << "Ergebnis = " << differenz << std::endl;
				// Funktionskörper des anderen Zustands
				if(checkForProblems(differenz)) return panic_S;
				if(hasProcessFinished(differenz)) return idle_S;
			}
		}

		state_T runState3(){
			while(true){
				int zahl1=0, zahl2=0, produkt=0;

				std::cout << "Geben Sie 2 Zahlen zur multiplikation ein:" << std::endl;
				std::cin >> zahl1;
				std::cin >> zahl2;
				
				produkt=zahl1*zahl2;

				std::cout << "Ergebnis=" << produkt << std::endl;
				// Neuer Zustand
				if(checkForProblems(produkt)) return panic_S;
				if(hasProcessFinished(produkt)) return idle_S;
			}	
		}

		state_T runIdle(){
			while(true){
				int Auswahl;
				std::cout << "Hallo, was möchtest du tun?" << "\n";
				std::cout << "(1) Addition" << "\n";
				std::cout << "(2) Subtraktion" << "\n";
				std::cout << "(3) Multiplikation" << "\n";
				std::cout << "(4) Programm beenden" << std::endl;

				std::cin >> Auswahl;

				//an dieser Stelle könnte auch eine LED blinken
				if(evaluateTransitionGuard1(Auswahl)) return state1_S;
				if(evaluateTransitionGuard2(Auswahl)) return state2_S;
				if(evaluateTransitionGuard3(Auswahl)) return state3_S;
				if(Auswahl==4) return exit_S;
			}
		}

	public:
		int exec(){
			while(nextState_ != exit_S){
				// Die States werden in diesem Switch alle sehr offensichtlich
				// aufgelistet. Um die Transitionsmechanik zu verstehen muss der
				// Programmierer in den jeweiligen Zustand schauen.
				switch(nextState_)
				{
					default:
					case panic_S:
						nextState_ = panic();
						break;
					case idle_S:
						nextState_ = runIdle();
						break;
					case state1_S:
						nextState_ = runState1();
						break;
					case state2_S:
						nextState_ = runState2();
						break;
					case state3_S:	//Neu
						nextState_ = runState3();
						break;
				}
			}
			// Wenn der Exit State erreicht wird, ist etwas schief gelaufen
			// Daher returnt die .exec Funktion eine 1 welche dann von main
			// an den Aufrufenden weitergegeben wird
			std::cout << "State-Machine beendet" << "\n";
			return 1;
		}

		stateEngine_T(int argc, char** argv){
			// Konstruktionsroutine die ggf. etwas mit den Übergabeparametern anfängt
			nextState_ = idle_S;
		}
	};
}


int main(int argc, char** argv){
	// Zunächste wird die Statemachine im Speicher angelegt
	local::stateEngine_T states{argc, argv};
	// Im Anschluss daran wird die eigentliche Engine ausgeführt.
	// Der Return-Value der Statemachine ist zugleich der Exit-Status-Code.

	/*	Eventuell ein Funktionsaufruf?	*/

	return states.exec();
}
