#include "wall.h"

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

std::ostream &operator<<(std::ostream &os, Wall const &wall) {
	return os << "(" << wall.pointA << "|" << wall.pointB << ")";
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

        token = token.substr(token.find(':') + 1);
        int colorR = std::stoi(token.substr(0, token.find(',')));
        token = token.substr(token.find(',') + 1);
        int colorG = std::stoi(token.substr(0, token.find(',')));
        token = token.substr(token.find(',') + 1);
        int colorB = std::stoi(token);

        node = new WallNode{{pointA, pointB, {colorR, colorG, colorB}}};
        node->left = readBinaryTree(node->left, fin);
        node->right = readBinaryTree(node->right, fin);
    }

    return node;
}

WallPosition getWallPosition(Wall parentWall, Wall wall) {
    float slope = (parentWall.pointB.y - parentWall.pointA.y) /  (parentWall.pointB.x - parentWall.pointA.x);
    float yInt = parentWall.pointA.y + (-slope * parentWall.pointA.x);
    
    if (wall.pointA.y > (slope * wall.pointA.x) + yInt) {
        return WALL_FRONT;
    }

    return WALL_BACK;
}

WallPosition getWallPosition(Wall parentWall, Vector2 point) {
    float slope = (parentWall.pointB.y - parentWall.pointA.y) /  (parentWall.pointB.x - parentWall.pointA.x);
    float yInt = parentWall.pointA.y + (-slope * parentWall.pointA.x);
    
    if (point.y > (slope * point.x) + yInt) {
        return WALL_FRONT;
    }

    return WALL_BACK;
}