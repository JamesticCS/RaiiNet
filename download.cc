#include "download.h"

bool Download::execute(Square* square) {
    return false;
}

bool Download::execute(Link* link) {
    if (used || !link || link->isDownloaded()) return false;
    link->setDownloaded();
    used = true;
    return true;
}

std::string Download::abilityName() const {
    return "Download";
}
