#pragma once
# define M_PI           3.14159265358979323846
template <typename T>
class Vector3 {
public:
    Vector3() : x(T()), y(T()), z(T()) {}
    Vector3(T x, T y, T z) : x(x), y(y), z(z) {}

    T getX() const { return x; }
    T getY() const { return y; }
    T getZ() const { return z; }

    void setX(T x) { this->x = x; }
    void setY(T y) { this->y = y; }
    void setZ(T z) { this->z = z; }

    T length() const { return std::sqrt(x * x + y * y + z * z); }

    Vector3 normalize() const {
        T len = length();
        return Vector3(x / len, y / len, z / len);
    }

    T dot(const Vector3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    Vector3 cross(const Vector3& other) const {
        return Vector3(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }

private:
    T x, y, z;
};