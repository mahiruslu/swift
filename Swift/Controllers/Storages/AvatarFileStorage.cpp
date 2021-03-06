/*
 * Copyright (c) 2010-2019 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#include <Swift/Controllers/Storages/AvatarFileStorage.h>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

#include <Swiften/Base/Log.h>
#include <Swiften/Base/String.h>
#include <Swiften/Crypto/CryptoProvider.h>
#include <Swiften/StringCodecs/Hexify.h>

namespace Swift {

AvatarFileStorage::AvatarFileStorage(const boost::filesystem::path& avatarsDir, const boost::filesystem::path& avatarsFile, CryptoProvider* crypto) : avatarsDir(avatarsDir), avatarsFile(avatarsFile), crypto(crypto) {
    if (boost::filesystem::exists(avatarsFile)) {
        try {
            boost::filesystem::ifstream file(avatarsFile);
            std::string line;
            if (file.is_open()) {
                while (!file.eof()) {
                    getline(file, line);
                    std::pair<std::string, std::string> r = String::getSplittedAtFirst(line, ' ');
                    JID jid(r.second);
                    if (jid.isValid()) {
                        jidAvatars.insert(std::make_pair(jid, r.first));
                    }
                    else if (!r.first.empty() || !r.second.empty()) {
                        SWIFT_LOG(error) << "Invalid entry in avatars file: " << r.second;
                    }
                }
            }
        }
        catch (...) {
            SWIFT_LOG(error) << "Error reading avatars file";
        }
    }
}

bool AvatarFileStorage::hasAvatar(const std::string& hash) const {
    return boost::filesystem::exists(getAvatarPath(hash));
}

void AvatarFileStorage::addAvatar(const std::string& hash, const ByteArray& avatar) {
    assert(Hexify::hexify(crypto->getSHA1Hash(avatar)) == hash);

    boost::filesystem::path avatarPath = getAvatarPath(hash);
    if (!boost::filesystem::exists(avatarPath.parent_path())) {
        try {
            boost::filesystem::create_directories(avatarPath.parent_path());
        }
        catch (const boost::filesystem::filesystem_error& e) {
            SWIFT_LOG(error) << "filesystem error: " << e.what();
        }
    }

    try {
        boost::filesystem::ofstream file(avatarPath, boost::filesystem::ofstream::binary|boost::filesystem::ofstream::out);
        file.write(reinterpret_cast<const char*>(vecptr(avatar)), static_cast<std::streamsize>(avatar.size()));
    }
    catch (const boost::filesystem::filesystem_error& e) {
        SWIFT_LOG(error) << "filesystem error: " << e.what();
    }
}

boost::filesystem::path AvatarFileStorage::getAvatarPath(const std::string& hash) const {
    return avatarsDir / hash;
}

ByteArray AvatarFileStorage::getAvatar(const std::string& hash) const {
    ByteArray data;
    try {
        readByteArrayFromFile(data, getAvatarPath(hash));
    }
    catch (const boost::filesystem::filesystem_error& e) {
        SWIFT_LOG(error) << "filesystem error: " << e.what();
    }
    return data;
}

void AvatarFileStorage::setAvatarForJID(const JID& jid, const std::string& hash) {
    std::pair<JIDAvatarMap::iterator, bool> r = jidAvatars.insert(std::make_pair(jid, hash));
    if (r.second) {
        saveJIDAvatars();
    }
    else if (r.first->second != hash) {
        r.first->second = hash;
        saveJIDAvatars();
    }
}

std::string AvatarFileStorage::getAvatarForJID(const JID& jid) const {
    JIDAvatarMap::const_iterator i = jidAvatars.find(jid);
    return i == jidAvatars.end() ? "" : i->second;
}

void AvatarFileStorage::saveJIDAvatars() {
    try {
        boost::filesystem::ofstream file(avatarsFile);
        for (JIDAvatarMap::const_iterator i = jidAvatars.begin(); i != jidAvatars.end(); ++i) {
            file << i->second << " " << i->first.toString() << std::endl;
        }
        file.close();
    }
    catch (...) {
        SWIFT_LOG(error) << "Error writing avatars file";
    }
}

}
