module square;

bool Square::hasLink() const {
   // placeholder
   return false;
   // return link != nullptr;
}

bool Square::isEmpty() const {
   // placeholder
   return true;
   
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