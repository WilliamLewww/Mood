#include "wall.h"

std::ostream &operator<<(std::ostream &os, Wall const &wall) {
	return os << "(" << wall.pointA << "|" << wall.pointB << ")";
}

void printTree(WallNode* root, const std::string& prefix) {
    if (root == NULL) { return; }

    bool hasLeft = (root->left != NULL);
    bool hasRight = (root->right != NULL);

    if (!hasLeft && !hasRight) { return; }

    std::cout << prefix;
    std::cout << ((hasLeft  && hasRight) ? "----" : "");
    std::cout << ((!hasLeft && hasRight) ? "----" : "");

    if (hasRight) {
        bool printStrand = (hasLeft && hasRight && (root->right->right != NULL || root->right->left != NULL));
        std::string newPrefix = prefix + (printStrand ? "|   " : "    ");
        std::cout << "F: " << root->right->splitter << std::endl;
        printTree(root->right, newPrefix);
    }

    if (hasLeft) {
        std::cout << (hasRight ? prefix : "") << "----" << "B: " << root->left->splitter << std::endl;
        printTree(root->left, prefix + "    ");
    }
}

WallNode* readBinaryTree(WallNode *node, std::ifstream &fin) {
	std::string token;
	fin >> token;

	if (token == "#") { return nullptr; }
	else {
		token.erase(std::remove(token.begin(), token.end(), '('), token.end());
		token.erase(std::remove(token.begin(), token.end(), ')'), token.end());

		std::string pointAS = token.substr(0, token.find('|'));
		std::string pointBS = token.substr(token.find('|') + 1);

		Vector2 pointA = { std::stof(pointAS.substr(0, pointAS.find(','))), std::stof(pointAS.substr(pointAS.find(',') + 1)) };
		Vector2 pointB = { std::stof(pointBS.substr(0, pointBS.find(','))), std::stof(pointBS.substr(pointBS.find(',') + 1)) };

		node = new WallNode{{pointA, pointB}};
		node->left = readBinaryTree(node->left, fin);
	 	node->right = readBinaryTree(node->right, fin);
	}

	return node;
}