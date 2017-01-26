#include "Utility.h"

int Utility::getTileXFromInt(int x) {
	return (x % 32);
};
int Utility::getTileYFromInt(int x) {
	return ((x - x % 32) / 32);
};

int Utility::getXFromInt(int x) {
	return (x % 32) * 32 * 2 + 16;
};
int Utility::getYFromInt(int x) {
	return ((x - x % 32) / 32) * 32 * 2 + 16;
};

int Utility::getXFromYAndX(int x, int y) {
	return (x + y * 32);
};

