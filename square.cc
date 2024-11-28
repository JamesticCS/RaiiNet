// square.cc
#include "square.h"
bool Square::hasLink() const {
   return link != nullptr;
}

bool Square::isEmpty() const {
   return !hasLink();
}
bool Square::hasFirewall() const {
   return firewall;
}

bool Square::isServerPort() const {
   return serverPort;
}

bool Square::isSideEdge() const {
   return sideEdge;
}

bool Square::isTopOrBottomEdge() const {
   return topOrBottomEdge;
}

void Square::placeFirewall(int playerId) {  
   firewall = true;
   firewallOwner = playerId;  
}

const std::unique_ptr<Link>& Square::getLink() const {
    return link;
}

std::unique_ptr<Link>& Square::getLink() {
    return link;
}

void Square::setLink(std::unique_ptr<Link> newLink) {
    link = std::move(newLink);
}

void Square::removeLink() {
    link = nullptr;
}