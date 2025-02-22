#ifndef GROUP_H
#define GROUP_H

#include <list>
#include <string>
#include <iostream>
#include <memory>
#include "Multimedia.h" // car on utilise des objets Multimedia (Photo, Video, Film)

using smart_pointer = std::shared_ptr<Multimedia>;
class Database;

class Group : public std::list<smart_pointer> {
    private:
        std::string name;

    public:
        Group(const std::string& name) : name(name) {}

        std::string getName() const {
            return name;
        }

        void setName(const std::string& name) {
            this->name = name;
        }

        void display(std::ostream& stream) const {
            stream << "Groupe " << name << " :" << std::endl;
            for (const auto& item : *this) {
                item->display(stream);
            }
        }

        void write(std::ostream& os) const {
            os << "Group " << name << " " << size() << " ";
            for (const auto& media : *this) {
                os << media->getName() << " ";
            }
            os << "\n";
        }
        
        void read(std::istream& is, const Database& db);
};

#endif // GROUP_H