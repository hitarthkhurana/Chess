#ifndef MOVE_H
#define MOVE_H

// Mutable data struct (like std::pair)
struct Move {
	int r1, c1, r2, c2; // Primary move positions
	int r3, c3, r4, c4; // Castling positions
	bool castle;        // Is castling?
	bool enPassant;     // Is en passant?
	int promotion;      // Pawn promotion

	// Types of promotion
	enum Promotion {
		NONE = 0, QUEEN, ROOK, BISHOP, KNIGHT
	};

	Move();
	Move(int r1, int c1, int r2, int c2);
	Move(int r1, int c1, int r2, int c2, bool enPassant);
	Move(int r1, int c1, int r2, int c2, int promotion);
	Move(int r1, int c1, int r2, int c2, int r3, int c3, int r4, int c4);
};

#endif
