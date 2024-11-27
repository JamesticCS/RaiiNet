module square;

bool Square::hasLink() const {
   return link != nullptr;
}

bool Square::isEmpty() const {
   !hasLink();
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

Link* Square::getLink() const {
    return link.get();
}

void Square::setLink(std::unique_ptr<Link> newLink) {
    link = std::move(newLink);
}

void Square::removeLink() {
    link = nullptr;
}