#include "pathfinding.h"

using namespace std::placeholders;

bool Vec2i::operator == (const Vec2i& coordinates_) const
{
    return (x == coordinates_.x && y == coordinates_.y);
}

Vec2i operator + (const Vec2i& left_, const Vec2i& right_)
{
    return{ left_.x + right_.x, left_.y + right_.y };
}

Node::Node(Vec2i coordinates_, Node *parent_)
{
    parent = parent_;
    coordinates = coordinates_;
    G = H = 0;
}

unsigned int Node::getScore() const
{
    return G + H;
}

//CoordinateList PathFinding::direction = {
//    { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 },
//    { -1, -1 }, { 1, 1 }, { -1, 1 }, { 1, -1 }
//};
//CoordinateList PathFinding::walls = { };
//Vec2i PathFinding::worldSize = { -1, -1 };

/*PathFinding *PathFinding::pF = nullptr;

PathFinding::PathFinding()
{
    direction = {
        { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 },
        { -1, -1 }, { 1, 1 }, { -1, 1 }, { 1, -1 }
    };
}*/

PathFinding::PathFinding()
{
    direction = {
        { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 },
        { -1, -1 }, { 1, 1 }, { -1, 1 }, { 1, -1 }
    };
    walls = { };
    worldSize = { -1, -1 };
}

void PathFinding::loadMap(QStringList map)
{
    walls.clear();
    if(map.isEmpty())
        return;
    worldSize = { map[0].size(), map.size() };
    for(int i = 0 ; i < worldSize.y ; i++)
    {
        for(int j = 0 ; j < worldSize.x ; j++)
        {
            if(map[i][j] == '0')
                walls.push_back({j, i});
        }
    }
}

CoordinateList PathFinding::findPath(Vec2i source_, Vec2i target_)
{
    if(detectCollision(source_) || detectCollision(target_))
        return {{-1, -1}};
    Node *current = nullptr;
    NodeSet openSet, closedSet;
    openSet.insert(new Node(source_));
    while (!openSet.empty())
    {
        current = *openSet.begin();
        for (auto node : openSet)
        {
            if (node->getScore() <= current->getScore())
                current = node;
        }
        if (current->coordinates == target_)
            break;
        closedSet.insert(current);
        openSet.erase(std::find(openSet.begin(), openSet.end(), current));
        for (int i = 0; i < 8; ++i)
        {
            Vec2i newCoordinates(current->coordinates + direction[i]);
            if (detectCollision(newCoordinates) || findNodeOnList(closedSet, newCoordinates))
                continue;
            unsigned int totalCost = current->G + ((i < 4) ? 10 : 14);
            Node *successor = findNodeOnList(openSet, newCoordinates);
            if (successor == nullptr)
            {
                successor = new Node(newCoordinates, current);
                successor->G = totalCost;
                successor->H = 2*static_cast<unsigned int>(octagonal(successor->coordinates, target_));
                openSet.insert(successor);
            }
            else if (totalCost < successor->G)
            {
                successor->parent = current;
                successor->G = totalCost;
            }
        }
    }
    CoordinateList path;
    while (current != nullptr)
    {
        path.insert(path.begin(), current->coordinates);
        current = current->parent;
    }
    releaseNodes(openSet);
    releaseNodes(closedSet);
    return path;
}

CoordinateList PathFinding::findPath(Vec2i source_, Vec2i target_, double range, bool keepSight)
{
    if(detectCollision(source_) || detectCollision(target_))
        return {{-1, -1}};
    Node *current = nullptr;
    NodeSet openSet, closedSet;
    openSet.insert(new Node(source_));
    while (!openSet.empty())
    {
        current = *openSet.begin();
        for (auto node : openSet)
        {
            if (node->getScore() <= current->getScore())
                current = node;
        }
        if (current->coordinates == target_)
            break;
        if(range >= distance(target_, current->coordinates))
        {
            if(keepSight)
            {
                if(hasSight(target_, current->coordinates))
                    break;
            }
            else
                break;
        }
        closedSet.insert(current);
        openSet.erase(std::find(openSet.begin(), openSet.end(), current));
        for (int i = 0; i < 8; ++i)
        {
            Vec2i newCoordinates(current->coordinates + direction[i]);
            if (detectCollision(newCoordinates) || findNodeOnList(closedSet, newCoordinates))
                continue;
            unsigned int totalCost = current->G + ((i < 4) ? 10 : 14);
            Node *successor = findNodeOnList(openSet, newCoordinates);
            if (successor == nullptr)
            {
                successor = new Node(newCoordinates, current);
                successor->G = totalCost;
                successor->H = 2 * static_cast<unsigned int>(octagonal(successor->coordinates, target_));
                openSet.insert(successor);
            }
            else if (totalCost < successor->G)
            {
                successor->parent = current;
                successor->G = totalCost;
            }
        }
    }
    CoordinateList path;
    while (current != nullptr)
    {
        path.insert(path.begin(), current->coordinates);
        current = current->parent;
    }
    releaseNodes(openSet);
    releaseNodes(closedSet);
    return path;
}

double PathFinding::distance(Vec2i src, Vec2i dst)
{
    return sqrt((src.x - dst.x) * (src.x - dst.x) + (src.y - dst.y) * (src.y - dst.y));
}

/*PathFinding *PathFinding::getInstance()
{
    if(pF == nullptr)
        pF = new PathFinding();
    return pF;
}*/

bool PathFinding::hasSight(Vec2i src, Vec2i dest)
{
    int dx = abs(dest.x - src.x);
    int dy = abs(dest.y - src.y);
    int sx = src.x < dest.x ? 1 : -1;
    int sy = src.y < dest.y ? 1 : -1;
    int err = (dx>dy ? dx : -dy)/2;
    int e2;
    for(;;)
    {
        if(detectCollision(src))
            return false;
        if (src.x==dest.x && src.y==dest.y) break;
        e2 = err;
        if (e2 >-dx) { err -= dy; src.x += sx; }
        if (e2 < dy) { err += dx; src.y += sy; }
    }
    return true;
}

Node* PathFinding::findNodeOnList(NodeSet& nodes_, Vec2i coordinates_)
{
    for (auto node : nodes_)
    {
        if (node->coordinates == coordinates_)
            return node;
    }
    return nullptr;
}

void PathFinding::releaseNodes(NodeSet& nodes_)
{
    for (auto it = nodes_.begin(); it != nodes_.end();)
    {
        delete *it;
        it = nodes_.erase(it);
    }
}

bool PathFinding::detectCollision(Vec2i coordinates_)
{
    if (coordinates_.x < 0 || coordinates_.x >= worldSize.x ||
        coordinates_.y < 0 || coordinates_.y >= worldSize.y ||
        std::find(walls.begin(), walls.end(), coordinates_) != walls.end())
        return true;
    return false;
}

int PathFinding::octagonal(Vec2i source_, Vec2i target_)
{
    Vec2i delta =
    {
        abs(source_.x - target_.x),
        abs(source_.y - target_.y)
    };
    return 10 * (delta.x + delta.y) + (-6) * std::min(delta.x, delta.y);
}
