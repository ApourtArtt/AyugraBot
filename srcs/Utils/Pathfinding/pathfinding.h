#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <vector>
#include <functional>
#include <set>
#include <QStringList>
#include <algorithm>
#include <tgmath.h>

struct Vec2i
{
    int x, y;
    bool operator == (const Vec2i& coordinates_) const;
};

using CoordinateList = QVector<Vec2i>;

struct Node
{
    unsigned int G, H;
    Vec2i coordinates;
    Node *parent;
    /*~Node(){ if(parent != nullptr) delete parent; }
    Node(const Node &node)
    {
        this->G = node.G;
        this->H = node.H;
        this->coordinates = node.coordinates;
        this->parent = node.parent;
        *this = node;
    }*/
    Node(Vec2i coord_, Node *parent_ = nullptr);
    unsigned int getScore() const;
};

using NodeSet = std::set<Node*>;

class PathFinding
{
public:
    PathFinding();
    void loadMap(QStringList map);
    bool hasSight(Vec2i src, Vec2i dest);
    CoordinateList findPath(Vec2i source_, Vec2i target_);
    CoordinateList findPath(Vec2i source_, Vec2i target_, double range, bool keepSight);
    static double distance(Vec2i src, Vec2i dst);

private:
    bool detectCollision(Vec2i coordinates_);
    Node* findNodeOnList(NodeSet& nodes_, Vec2i coordinates_);
    void releaseNodes(NodeSet& nodes_);
    int octagonal(Vec2i source_, Vec2i target_);
    CoordinateList direction, walls;
    Vec2i worldSize;
};

#endif // PATHFINDING_H
