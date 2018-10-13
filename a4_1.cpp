/*
 Name:        Michael
 Date:        September 12, 2018
 Instructor:  Dave Harden
 File Name:   a4_1.cpp
 Description:
 
 The main objective of this program is to simulate a limited game of poker where the user has to use the command line interface to choose five card numbers between two and nine.  Once the five cards are choosen, the program determines what type of hand the user has and excludes all other hands.
 
 
 */

#include<iostream>
using namespace std;

const int CARDS_IN_HAND = 5;
const int LOWEST_CARD = 2;
const int HIGHEST_CARD = 9;
const string EMPTY_STRING;

void chooseCards(int hand[]);
int  incrementIfValidValue(int hand[], int &cardValue, int count);
void initCardIndicesArray(int cardIndices[], const int hand[]);
void setAllElementsToZero(int cardIndices[]);
int  numberOfCardRepeats(const int cardIndices[], int repeats);
bool containsHighCard(const int hand[]);
bool containsPair(const int hand[]);
bool containsTwoPairs(const int hand[]);
bool containsThreeOfAKind(const int hand[]);
bool containsStraight(const int hand[]);
bool containsFullHouse(const int hand[]);
bool containsFourOfAKind(const int hand[]);
bool cardIndicesAreContiguousAndSingular(const int cardIndices[], int firstCardReached);

int main() {
    int hand[CARDS_IN_HAND];
    chooseCards(hand);
    cout << ((containsPair(hand)) ?  "Pair!\n" : EMPTY_STRING) ;
    cout << ((containsTwoPairs(hand)) ? "Two pairs!\n" : EMPTY_STRING);
    cout << ((containsThreeOfAKind(hand)) ? "Three of a kind!\n" : EMPTY_STRING );
    cout << ((containsStraight(hand))? "Straight!\n": EMPTY_STRING );
    cout << ((containsFullHouse(hand)) ? "Full house!\n" : EMPTY_STRING );
    cout << ((containsFourOfAKind(hand))  ? "Four of a kind!\n" : EMPTY_STRING);
    cout << ((containsHighCard(hand))? "High Card!\n" : EMPTY_STRING );
    
}






/**
 * This function lets the user choose five cards between 2 - 9
 * @param hand is the array that is referrenced and filled with five cards
 */
void chooseCards(int hand[]) {
    int count = 0, cardValue;
    cout << "Enter five numeric cards, no face cards. Use 2 - 9." << endl;
    while(count < CARDS_IN_HAND) {
        count += incrementIfValidValue(hand, cardValue, count);
    }
    
}






/**
 * Determines if the card number the user chose is within the correct range
 * @param hand represents the user's poker hand of five cards
 * @param count represents the index
 * @return 1 if the cards value is valid, 0 otherwise
 */
int incrementIfValidValue(int hand[], int &cardValue, int count){
    cout << "Card " << (count + 1) << ": ";
    cin >> cardValue;
    if( cardValue >= LOWEST_CARD && cardValue <= HIGHEST_CARD ){
        hand[count] = cardValue;
        return 1;
    }else{
        cout << "The card must be between 2 and 9\n" ;
        return 0;
    }
}






/**
 * Determines if the user's hand contains no repeating cards nor a straight
 * @param hand represents the user's poker hand of five cards
 * @return true if there are no repeating cards nor a straight, false otherwise
 */
bool containsHighCard(const int hand[]){
    bool containsNoPair =         !containsPair(hand);
    bool containsNoTwoPair =      !containsTwoPairs(hand);
    bool containsNoThreeOfAKind = !containsThreeOfAKind(hand);
    bool containsNoStraight =     !containsStraight(hand);
    bool containsNoFullHouse =    !containsFullHouse(hand);
    bool containsNoFourOfAKind =  !containsFourOfAKind(hand);
    return containsNoPair && containsNoTwoPair && containsNoThreeOfAKind
    && containsNoStraight && containsNoFullHouse && containsNoFourOfAKind;
}






/**
 * Determines if the user hand contains only one pair
 * @param hand represents the user's poker hand of five cards
 * @return true if the hand has only one pair
 */
bool containsPair(const int hand[]){
    bool containsOnePair = numberOfCardRepeats(hand,  2) == 1;
    bool containsNoThreeOfAKind = numberOfCardRepeats(hand, 3) == 0;
    return containsOnePair && containsNoThreeOfAKind;
}






/**
 * Determines if the user hand contains only one pair
 * @param hand represents the user's poker hand of five cards
 * @return true if the hand has only one pair
 */
bool containsTwoPairs(const int hand[]){
    return (numberOfCardRepeats(hand,  2) == 2);
}





/**
 * Determines if the user hand contains a three of a kind
 * @param hand represents the user's poker hand of five cards
 * @return true if the hand has only a three of a kind
 */
bool containsThreeOfAKind(const int hand[]){
    bool containsAThreeOfAKind = numberOfCardRepeats(hand,  3) == 1;
    bool containsNoPairs = numberOfCardRepeats(hand, 2) == 0;
    return containsAThreeOfAKind && containsNoPairs;
}






/**
 * Determines if the user hand contains a straight
 * @param hand represents the user's poker hand of five cards
 * @return true if the entire hand is a straight
 */
bool containsStraight(const int hand[]){
    int cardIndices[HIGHEST_CARD];
    initCardIndicesArray(cardIndices, hand);
    int count = 0;
    while(cardIndices[count] == 0){
        count++;
    }
    return cardIndicesAreContiguousAndSingular(cardIndices, count);
}






/**
 * Determines if the hand, from a given starting point, are 'straight'.
 * In other words, if the cards were choosen once and that they are all contiguous
 * between one another
 *
 * @param cardIndices is an array where the indices represent the card number
 * and the element represents the number of repeats for a given card
 * @param firstCardReached represents the first card in the card indices array
 * that isgreater than 0
 * @return true if if the cards indices are contiguous and contain no repeats
 */
bool cardIndicesAreContiguousAndSingular(const int cardIndices[], int firstCardReached){
    int count = firstCardReached, terminatingCard = firstCardReached + 4;
    if(terminatingCard > HIGHEST_CARD){
        return false;
    }
    while(count <= terminatingCard){
        if(cardIndices[count] != 1){
            return false;
        }
        count++;
    }
    return true;
}






/**
 * Determines if the user hand contains a full house
 * @param hand represents the user's poker hand of five cards
 * @return true if the user's hand is a full house
 */
bool containsFullHouse(const int hand[]){
    bool containsThreeOfAKind = numberOfCardRepeats(hand,  3) == 1;
    bool containsOnePair = numberOfCardRepeats(hand, 2) == 1;
    return containsThreeOfAKind && containsOnePair;
}






/**
 * Determines if the user hand contains a four of a kind
 * @param hand represents the user's poker hand of five cards
 * @return true if the user's hand contains a four of a kind
 */
bool containsFourOfAKind(const int hand[]){
    return (numberOfCardRepeats(hand,  4) == 1);
}

int numberOfCardRepeats(const int hand[], int repeats){
    int cardIndices[ (HIGHEST_CARD+1 )]; //This has to be one value higher due to the number nine being stored in the index 9;
    initCardIndicesArray(cardIndices, hand);
    int count, numberOfRepeats = 0;
    for(count = 0; count <= HIGHEST_CARD; count++){
        //cout << "\tcardIndices[" << count << "] = " << cardIndices[count] << endl;
        if(cardIndices[count] == repeats){
            numberOfRepeats++;
        }
    }
    return numberOfRepeats;
}






/**
 * Get all the card values of the hand array and store them as indices in the
 * cardIndices array so that the elements of that array represent
 * the number of cardrepeats.
 *
 * @param cardIndices is an array where the indices represent the card number
 * and the element represents the number of repeats for a given card
 * @param hand represents the user's hand of five cards
 */
void initCardIndicesArray(int cardIndices[], const int hand[]){
    setAllElementsToZero(cardIndices);
    int count;
    for(count = 0; count < CARDS_IN_HAND; count++ ){
        int cardValue = hand[count];
        cardIndices[cardValue] += 1;
    }
}






/**
 * Sets all elements of the cardIndices array to zero
 *
 * @param cardIndices is an array where the indices represent the card number
 * and the element represents the number of repeats for a given card
 */
void setAllElementsToZero(int cardIndices[]){
    int count;
    //Remember, the number 9 is in index 9, not index 8
    for(count = 0; count <= HIGHEST_CARD; count++ ){
        cardIndices[count] = 0;
    }
}

/*
 //High card
 Enter five numeric cards, no face cards. Use 2 - 9.
 Card 1: 2
 Card 2: 3
 Card 3: 5
 Card 4: 7
 Card 5: 9
 High Card!
 Program ended with exit code: 0
 
//Pair
 Enter five numeric cards, no face cards. Use 2 - 9.
 Card 1: 2
 Card 2: 3
 Card 3: 3
 Card 4: 4
 Card 5: 5
 Pair!
 Program ended with exit code: 0
 
 //Two pair
 Enter five numeric cards, no face cards. Use 2 - 9.
 Card 1: 9
 Card 2: 9
 Card 3: 6
 Card 4: 6
 Card 5: 5
 Two pairs!
 Program ended with exit code: 0
 
 //Three of a kind
 Enter five numeric cards, no face cards. Use 2 - 9.
 Card 1: 3
 Card 2: 3
 Card 3: 3
 Card 4: 2
 Card 5: 5
 Three of a kind!
 Program ended with exit code: 0
 
 //Straight
 Enter five numeric cards, no face cards. Use 2 - 9.
 Card 1: 2
 Card 2: 3
 Card 3: 4
 Card 4: 5
 Card 5: 6
 Straight!
 Program ended with exit code: 0
 
 //Four of a kind
 Enter five numeric cards, no face cards. Use 2 - 9.
 Card 1: 5
 Card 2: 5
 Card 3: 5
 Card 4: 5
 Card 5: 6
 Four of a kind!
 Program ended with exit code: 0
*/



