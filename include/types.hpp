/**
 * @file types.hpp
 * @author Julien Lin
 * @brief This file contains the daclaration of the class position_t and
 * RGBColor.
 * @version 0.1
 * @date 2020-02-09
 *
 */
#ifndef __TYPES_H_
#define __TYPES_H_

#include <cmath>
#include <cstdint>
#include <iostream>
#include <ostream>
#include <sstream>
#include <tuple>

/**
 * @brief This class define the position coordinatein the scene.
 * @class position_t
 */
class position_t {
public:
  double x; /**< Define the width in the scene. */
  double y; /**< Define the deepth in the scene. */
  double z; /**< Define the heigth in the scene. */

  /**
   * @brief Construct a new position t object
   *
   */
  position_t() : x(0), y(0), z(0) {}

  /**
   * @brief Construct a new position t object
   *
   * @param x Define the width in the scene.
   * @param y Define the deepth in the scene.
   * @param z Define the heigth in the scene.
   */
  position_t(double x, double y, double z) : x(x), y(y), z(z) {}

  /**
   * @brief Construct a new position t object
   *
   * @param pos Another position;
   */
  position_t(const position_t &pos) = default;

  /**
   * @brief Construct a new position t object
   *
   * @param pos Another position.
   */
  position_t(position_t &&pos) = default;

  /**
   * @brief Overloading the operator of division. A new position_t is generated.
   *
   * @param c a scalar of type double.
   * @return position_t
   */
  position_t operator/(const double c) const;

  /**
   * @brief Overloading the operator of multiplication by a dot product. A new
   * position_t is generated.
   *
   * @param pos Another position.
   * @return double
   */
  double operator*(const position_t pos) const;

  /**
   * @brief Overloading the operator of multiplication by a multiplication
   * operation by a scalar. A new position_t is generated.
   *
   * @param c a scalar.
   * @return position_t
   */
  position_t operator*(const double c) const;

  /**
   * @brief Overloading the operator of addition for vectoriel addition. A new
   * position_t is generated.
   *
   * @param pos Another position.
   * @return position_t
   */
  position_t operator+(const position_t &pos) const;

  /**
   * @brief Overloading the operator of substraction for vectoriel addition. A
   * new position_t is generated.
   *
   * @param pos Another position.
   * @return position_t
   */
  position_t operator-(const position_t &pos) const;

  /**
   * @brief Overloading equal operator.
   *
   * @param pos Another position.
   * @return position_t&
   */
  position_t &operator=(const position_t &pos);

  /**
   * @brief Overloading operator.
   *
   * @param pos Another position.
   * @return position_t&
   */
  position_t &operator+=(const position_t &pos);

  /**
   * @brief Overloading operator.
   *
   * @param pos Another position.
   * @return position_t&
   */
  position_t &operator-=(const position_t &pos);

  /**
   * @brief Overloading operator.
   *
   * @param pos Another position.
   * @return position_t&
   */
  position_t &operator*=(const double coef);

  /**
   * @brief Overloading operator. This operator is the cross product. A new
   * position_t is generated.
   *
   * @return position_t
   */
  position_t operator^(const position_t &);

  /**
   * @brief Overloading the unary operator. A new position_t is generated.
   *
   * @return position_t
   */
  position_t operator-() const;

  /**
   * @brief Overloading the unary operator. A new position_t is generated.
   *
   * @return position_t
   */
  position_t operator-();

  /**
   * @brief Overloading the equals operator.
   *
   * @return true if both are describing the same position in the scene.
   * @return false if both are not describing the sam position in the scene.
   */
  bool operator==(const position_t &);

  /**
   * @brief Overloading operator <<.
   *
   * @param os an output stream.
   * @param pos a position.
   * @return std::ostream&
   */
  friend std::ostream &operator<<(std::ostream &os, const position_t &pos);

  /**
   * @brief Compute the norm of the position.
   *
   * @return double
   */
  double norm();

  /**
   * @brief Compute the norm of a given position.
   *
   * @param pos a position.
   * @return double
   */
  static double norm(const position_t &pos);

  /**
   * @brief This method normalize the position. This is useful for the vector
   * class.
   *
   * @return position_t&
   */
  position_t &normalize();

  /**
   * @brief this method return the string representation of the object.
   *
   *
   * @return the string representation of the position_t object.
   */
  std::string to_string() const;
};

position_t operator*(const double, const position_t);

/**
 * @brief Overloading operator *. A new position_t is generated.
 *
 * @return position_t
 */
position_t operator*(double, position_t);

/**
 * @brief Defining the type vector_t as an aliases of position_t.
 *
 */
using vector_t = position_t;

/**
 * @brief This class represents the color description of the scene.
 * @class RGBColor
 */
class RGBColor {
private:
  unsigned char m_red, m_green, m_blue;

  /**
   * @brief Cap the value of the color so that color doesn't exceed THRESHOLD.
   *
   * @return unsigned char
   */
  unsigned char cap(unsigned) const;

  /**
   * threshold is the max intensity value.
   *
   */
  static const unsigned char threshold = 255;

public:
  /**
   * @brief Construct a new RGBColor object. The color is black.
   *
   */
  RGBColor() : m_red(0), m_green(0), m_blue(0) {}

  /**
   * @brief Construct a new RGBColor object.
   *
   * @param red intensity of the red color.
   * @param green intensity of the green color.
   * @param blue intensity of the blue color.
   */
  RGBColor(unsigned char red, unsigned char green, unsigned char blue)
      : m_red(red), m_green(green), m_blue(blue) {}

  /**
   * @brief Construct a new RGBColor object. This constructor is generated by
   * the compiler.
   *
   * @param color a RGBColor.
   */
  RGBColor(const RGBColor &color) = default;

  /**
   * @brief Construct a new RGBColor object. This constructor is generated by
   * the compiler.
   *
   * @param color a RGBColor.
   */
  RGBColor(RGBColor &&color) = default;

  /**
   * @brief Overloading swap function.
   *
   * @param other
   */
  void swap(RGBColor &other);

  /**
   * @brief Overloading << operator.
   *
   * @param os an output stream.
   * @param color a RGBColor.
   * @return std::ostream&
   */
  friend std::ostream &operator<<(std::ostream &os, const RGBColor &color);

  // Overriding operators
  /**
   * @brief Overloading the =  operator. After initialisation the content is
   * copied and the two instances remain.
   *
   * @return RGBColor&
   */
  RGBColor &operator=(const RGBColor &);

  /**
   * @brief Overloading * operator so RGBColor could works with double.
   *
   * @return RGBColor
   */
  RGBColor operator*(const double &)const;

  /**
   * @brief Overloading + operator so RGBColor could works with double.
   *
   *
   * @return RGBColor
   */
  RGBColor operator+(const RGBColor &) const;

  /**
   * @brief Overloading += operator. The content of the caller instance is add
   * with the content of the parameter. The content of the parmater doesn't
   * change.
   *
   * @return RGBColor&
   */
  RGBColor &operator+=(const RGBColor &);

  /**
   * @brief Return the string representation of the RGBColor object.
   *
   * @return string representation of the RGBColor object.
   */
  std::string to_string() const;
};

/**
 * @brief Overloading swap function.
 *
 */
void swap(RGBColor &, RGBColor &);

/**
 * @brief Overloading * operator so RGBColor could works with double. a new
 * RGBColor is created.
 *
 * @return RGBColor
 */
RGBColor operator*(double, const RGBColor &);

const position_t POSITION_T_NULL = position_t(0, 0, 0);

/**
 * E1 defines the unit vector in the direction of x in position_t.
 */
const vector_t E1 = vector_t(1, 0, 0);

/**
 * E2 defines the unit vector in the direction of y in position_t.
 */
const vector_t E2 = vector_t(0, 1, 0);

/**
 * E3 defines the unit vector in the direction of z in position_t.
 */
const vector_t E3 = vector_t(0, 0, 1);

/**
 * Defining white color in RGBColor.
 *
 */
const RGBColor RGB_WHITE = RGBColor(255, 255, 255);

/**
 * Defining black color in RGBColor.
 *
 */
const RGBColor RGB_BLACK = RGBColor(0, 0, 0);

/**
 * Defining red color in RGBColor.
 *
 */
const RGBColor RGB_RED = RGBColor(255, 0, 0);

/**
 * Defining green color in RGBColor.
 *
 */
const RGBColor RGB_GREEN = RGBColor(0, 255, 0);

/**
 * Defining blue color in RGBColor.
 *
 */
const RGBColor RGB_BLUE = RGBColor(0, 0, 255);

/**
 * Defining silver grey color in RGBColor.
 *
 */
const RGBColor RGB_SILVER_GREY = RGBColor(192, 192, 192);

#endif // __TYPES_H_
