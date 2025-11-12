#include <iostream>
#include <cstring>
#include <atomic>

class String {
private:
    static const size_t SSO_THRESHOLD = 15; // up to 15 chars stored locally

    struct SharedData {
        std::atomic<size_t> refCount;
        size_t length;
        char* data;

        SharedData(const char* src, size_t len) : refCount(1), length(len) {
            data = new char[len + 1];
            std::memcpy(data, src, len);
            data[len] = '\0';
        }

        ~SharedData() {
            delete[] data;
        }
    };

    bool isSSO;
    union {
        char ssoData[SSO_THRESHOLD + 1]; // for small strings
        SharedData* shared;              // for large strings
    };
    size_t length;

    void detach() {
        // If shared and refCount > 1, make a private copy
        if (!isSSO && shared->refCount > 1) {
            SharedData* old = shared;
            shared = new SharedData(old->data, old->length);
            old->refCount--;
        }
    }

public:
    // Constructors
    String(const char* str = "") {
        length = std::strlen(str);
        if (length <= SSO_THRESHOLD) {
            isSSO = true;
            std::memcpy(ssoData, str, length + 1);
        } else {
            isSSO = false;
            shared = new SharedData(str, length);
        }
    }

    // Copy constructor (COW)
    String(const String& other) {
        length = other.length;
        isSSO = other.isSSO;
        if (isSSO) {
            std::memcpy(ssoData, other.ssoData, length + 1);
        } else {
            shared = other.shared;
            shared->refCount++;
        }
    }

    // Move constructor
    String(String&& other) noexcept {
        length = other.length;
        isSSO = other.isSSO;
        if (isSSO)
            std::memcpy(ssoData, other.ssoData, length + 1);
        else {
            shared = other.shared;
            other.shared = nullptr;
        }
        other.length = 0;
    }

    // Destructor
    ~String() {
        if (!isSSO && shared) {
            if (--shared->refCount == 0)
                delete shared;
        }
    }

    // Copy assignment (COW)
    String& operator=(const String& other) {
        if (this == &other) return *this;

        // clean up current
        if (!isSSO && shared && --shared->refCount == 0)
            delete shared;

        length = other.length;
        isSSO = other.isSSO;

        if (isSSO)
            std::memcpy(ssoData, other.ssoData, length + 1);
        else {
            shared = other.shared;
            shared->refCount++;
        }
        return *this;
    }

    // Modify a character (detaches if shared)
    char& operator[](size_t index) {
        if (index >= length) throw std::out_of_range("Index out of range");
        detach();
        return isSSO ? ssoData[index] : shared->data[index];
    }

    const char& operator[](size_t index) const {
        if (index >= length) throw std::out_of_range("Index out of range");
        return isSSO ? ssoData[index] : shared->data[index];
    }

    const char* c_str() const {
        return isSSO ? ssoData : shared->data;
    }

    size_t size() const { return length; }

    friend std::ostream& operator<<(std::ostream& os, const String& s) {
        os << s.c_str();
        return os;
    }
};

int main() {
    String a("Short");
    String b("This is a very long string that triggers heap allocation");
    String c = b; // shared (COW)
    
    std::cout << "a = " << a << "\n";
    std::cout << "b = " << b << "\n";
    std::cout << "c = " << c << "\n";

    c[0] = 't'; // triggers detach (COW copy)
    std::cout << "After modifying c:\n";
    std::cout << "b = " << b << "\n";
    std::cout << "c = " << c << "\n";
}
