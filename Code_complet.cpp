class Square {
private:
    int row;
    int col;

public:
    Square(int row, int col);

    int getRow() const;
    int getCol() const;
    void setRow(int row);
    void setCol(int col);
};

Square::Square(int row, int col) : row(row), col(col) {}

int Square::getRow() const {
    return 7 - row;
}

int Square::getCol() const {
    return col;
}

void Square::setRow(int row) {
    this->row = 7 - row;
}

void Square::setCol(int col) {
    this->col = col;
}

#include <string>

enum class Color {
    BLACK,  /**< Couleur noire */
    WHITE /**< Couleur blanche */
};


class Piece {
protected:
    std::string name;     /**< Nom de la pièce */
    Color color;          /**< Couleur de la pièce */
    Square position;      /**< Position de la pièce sur l'échiquier */

public:

    Piece(std::string name, Color color, Square position);

    std::string getName() const;


    Color getColor() const;

    Square getPosition() const;

    void setPosition(const Square& newPosition);


    virtual std::string toString() const;

    virtual bool isValidMove(const Square& destination) const = 0;
};

class Pawn : public Piece {
private:
    bool hasMoved; /**< Indique si le pion a déjà été déplacé */

public:
    Pawn(Color color, Square position);

    bool isValidMove(const Square& destination) const override;

    // Add a move method to update hasMoved
    void move(const Square& destination);
};



class King : public Piece {
public:
    King(Color color, Square position);

    bool isValidMove(const Square& destination) const override;
};

class Queen : public Piece {
public:
    Queen(Color color, Square position);

    bool isValidMove(const Square& destination) const override;
};


class Bishop : public Piece {
public:
    Bishop(Color color, Square position);

    bool isValidMove(const Square& destination) const override;
};


class Knight : public Piece {
public:

    Knight(Color color, Square position);

    bool isValidMove(const Square& destination) const override;
};


class Rook : public Piece {
public:

    Rook(Color color, Square position);

    bool isValidMove(const Square& destination) const override;
};


Piece::Piece(std::string name, Color color, Square position)
	: name(name), color(color), position(position) {}

std::string Piece::getName() const {
	return name;
}

Color Piece::getColor() const {
	return color;
}

Square Piece::getPosition() const {
	return position;
}

void Piece::setPosition(const Square& newPosition) {
	position = newPosition;
}

std::string Piece::toString() const {
	return name;
}



Pawn::Pawn(Color color, Square position)
	: Piece("\u2659", color, position), hasMoved(false) {}

bool Pawn::isValidMove(const Square& destination) const {
    int rowDiff = destination.getRow() - position.getRow();
    int colDiff = std::abs(destination.getCol() - position.getCol());
    if (color == Color::WHITE) {
        if ((rowDiff == 1 || rowDiff == 2) && colDiff == 0 && !hasMoved) {
            return true;
        }
        else if (rowDiff == 1 && colDiff == 1) {
            // Ajoutez ici une logique pour capturer une pièce diagonalement si nécessaire
            return true;
        }
    }
    else {
        if ((rowDiff == -1 || rowDiff == -2) && colDiff == 0 && !hasMoved) {
            return true;
        }
        else if (rowDiff == -1 && colDiff == 1) {
            // Ajoutez ici une logique pour capturer une pièce diagonalement si nécessaire
            return true;
        }
    }
    return false;
}




King::King(Color color, Square position)
	: Piece("\u2654", color, position) {}

bool King::isValidMove(const Square& destination) const {
	int rowDiff = std::abs(position.getRow() - destination.getRow());
	int colDiff = std::abs(position.getCol() - destination.getCol());
	return (rowDiff <= 1 && colDiff <= 1);
}



Queen::Queen(Color color, Square position)
	: Piece("\u2655", color, position) {}

bool Queen::isValidMove(const Square& destination) const {
	int rowDiff = std::abs(position.getRow() - destination.getRow());
	int colDiff = std::abs(position.getCol() - destination.getCol());
	return (rowDiff == colDiff) || (position.getRow() == destination.getRow()) || (position.getCol() == destination.getCol());
}



Bishop::Bishop(Color color, Square position)
	: Piece("\u2657", color, position) {}

bool Bishop::isValidMove(const Square& destination) const {
	int rowDiff = std::abs(position.getRow() - destination.getRow());
	int colDiff = std::abs(position.getCol() - destination.getCol());
	return (rowDiff == colDiff);
}



Knight::Knight(Color color, Square position)
	: Piece("\u2658", color, position) {}

bool Knight::isValidMove(const Square& destination) const {
	int rowDiff = std::abs(position.getRow() - destination.getRow());
	int colDiff = std::abs(position.getCol() - destination.getCol());
	return (rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2);
}


Rook::Rook(Color color, Square position)
	: Piece("\u2656", color, position) {}

bool Rook::isValidMove(const Square& destination) const {
	return (position.getRow() == destination.getRow()) || (position.getCol() == destination.getCol());
}

Board::Board() {
    board = new Piece**[8];
    for (int i = 0; i < 8; i++) {
        board[i] = new Piece*[8];
        for (int j = 0; j < 8; j++) {
            board[i][j] = nullptr;
        }
    }
}

Board::~Board() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            delete board[i][j];
        }
        delete[] board[i];
    }
    delete[] board;
}

Piece* Board::getPiece(int row, int col) {
    return board[7 - row][col];
}

void Board::placePieces() {
    // Placement des pièces blanches
    for (int i = 0; i < 8; i++) {
        board[6][i] = new Pawn(Color::BLACK, Square(6, i));
    }
    board[7][0] = new Rook(Color::BLACK, Square(7, 0));
    board[7][1] = new Knight(Color::BLACK, Square(7, 1));
    board[7][2] = new Bishop(Color::BLACK, Square(7, 2));
    board[7][3] = new Queen(Color::BLACK, Square(7, 3));
    board[7][4] = new King(Color::BLACK, Square(7, 4));
    board[7][5] = new Bishop(Color::BLACK, Square(7, 5));
    board[7][6] = new Knight(Color::BLACK, Square(7, 6));
    board[7][7] = new Rook(Color::BLACK, Square(7, 7));

    // Placement des pièces noires
    for (int i = 0; i < 8; i++) {
        board[1][i] = new Pawn(Color::WHITE, Square(1, i));
    }
    board[0][0] = new Rook(Color::WHITE, Square(0, 0));
    board[0][1] = new Knight(Color::WHITE, Square(0, 1));
    board[0][2] = new Bishop(Color::WHITE, Square(0, 2));
    board[0][3] = new Queen(Color::WHITE, Square(0, 3));
    board[0][4] = new King(Color::WHITE, Square(0, 4));
    board[0][5] = new Bishop(Color::WHITE, Square(0, 5));
    board[0][6] = new Knight(Color::WHITE, Square(0, 6));
	board[0][7] = new Rook(Color::WHITE, Square(0, 7));
}

void Board::movePiece(const Square& from, const Square& to) {
	Piece* piece = board[7 - from.getRow()][from.getCol()];
	if (piece == nullptr) {
		std::cout << "Il n'y a pas de pièce à déplacer à la position donnée." << std::endl;
		return;
	}

	if (piece->isValidMove(to)) {
		// Supprime la pièce à la destination si elle existe
		if (board[7 - to.getRow()][to.getCol()] != nullptr) {
			delete board[7 - to.getRow()][to.getCol()];
		}

		// Déplace la pièce
		board[7 - to.getRow()][to.getCol()] = piece;
		board[7 - from.getRow()][from.getCol()] = nullptr;

		// Met à jour la position de la pièce
		piece->setPosition(to);
	}
	else {
		std::cout << "Ce mouvement est invalide pour cette pièce." << std::endl;
	}
}

void Board::display() const {
	std::cout << "    a     b     c     d     e     f     g     h" << std::endl;
	std::cout << " +-----+-----+-----+-----+-----+-----+-----+-----+" << std::endl;

	for (int i = 7; i >= 0; --i) { // Inverser la numérotation des lignes
		for (int j = 0; j < 8; ++j) {
			if (j == 0) {
				std::cout << " | ";
			}
			if (board[i][j] == nullptr) {
				std::cout << "     | ";
			}
			else {
				std::cout << " " << board[i][j]->toString() << " | ";
			}
		}
		std::cout << std::endl;
		std::cout << " +-----+-----+-----+-----+-----+-----+-----+-----+" << std::endl;
	}
}

std::string Board::displayResults() const {
    std::string result = "";
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j] != nullptr) {
                result += board[i][j]->getColor() == Color::WHITE ? "w" : "b";
                if (board[i][j]->getName() == "\u2659") {
                    result += "P";
                } else if (board[i][j]->getName() == "\u2654") {
                    result += "K";
                } else if (board[i][j]->getName() == "\u2655") {
                    result += "Q";
                } else if (board[i][j]->getName() == "\u2657") {
                    result += "B";
                } else if (board[i][j]->getName() == "\u2658") {
                    result += "N";
                } else if (board[i][j]->getName() == "\u2656") {
                    result += "R";
                }
            }
            result += ",";
        }
    }
    return result;
}

class Game {
private:
    Board board; /**< Plateau de jeu */
    Color currentPlayer; /**< Joueur courant */

public:
    Game();

    void start();

private:
    void displayGameResult(const std::string& result);

    bool isValidMove(const std::string& move) const;

    bool makeMove(const std::string& move);

    void switchPlayer();
};

#include <iostream>
#include <regex>

Game::Game() : currentPlayer(Color::WHITE) {}

void Game::start() {
    board.placePieces();
    board.display();

    std::string move;
    while (true) {
        // std::cout << "Player " << (currentPlayer == Color::WHITE ? "White" : "Black") << ", enter your move: ";
        std::getline(std::cin, move);

        if (move == "/quit") {
            displayGameResult("?-?");
            break;
        } else if (move == "/resign") {
            std::string result = (currentPlayer == Color::WHITE ? "0-1" : "1-0");
            displayGameResult(result);
            break;
        } else if (move == "/draw") {
            displayGameResult("1/2-1/2");
            break;
        } else if (isValidMove(move)) {
            if (makeMove(move)) {
                board.display();
                switchPlayer();
            }
        } else {
            std::cout << "Invalid move. Please try again." << std::endl;
        }
    }
}

void Game::displayGameResult(const std::string& result) {
    std::cout << board.displayResults() << " " << result << std::endl;
}

bool Game::isValidMove(const std::string& move) const {
    std::regex moveRegex("^[a-h][1-8][a-h][1-8]$");
    return std::regex_match(move, moveRegex);
}


bool Game::makeMove(const std::string& move) {
    int fromCol = move[0] - 'a';
    int fromRow = move[1] - '1';
    int toCol = move[2] - 'a';
    int toRow = move[3] - '1';

    Square from(fromRow, fromCol);
    Square to(toRow, toCol);

    Piece* piece = board.getPiece(from.getRow(), from.getCol());

    if (piece == nullptr) {
        std::cout << "There is no piece at the specified position." << std::endl;
        return false;
    }

    if (piece->getColor() != currentPlayer) {
        std::cout << "It's not your turn." << std::endl;
        return false;
    }

    if (!piece->isValidMove(to)) {
        std::cout << "Invalid move for the selected piece." << std::endl;
        return false;
    }

    board.movePiece(from, to);
    return true;
}


void Game::switchPlayer() {
    currentPlayer = (currentPlayer == Color::WHITE) ? Color::BLACK : Color::WHITE;
}

#include "Game.hpp"

int main() {
    try {
        Game game;
        game.start();
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
