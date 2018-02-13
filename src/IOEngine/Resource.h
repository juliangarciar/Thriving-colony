#ifndef RESOURCE_H
#define RESOURCE_H

class Resource {
    public:
        void load(const char *path) = 0;

        void setIdentifier(const char *) = 0;
        const char *getIdentifier() = 0;
    private:
        const char *identifier;
}

#endif