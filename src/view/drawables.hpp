#ifndef DRAWABLES_HPP
#define DRAWABLES_HPP

#include <string>

#include "../utils/allegro_includes.hpp"
#include "../utils/observer.hpp"
#include "../utils/point.hpp"

using namespace std;

// Colors defined in your code
extern const ALLEGRO_COLOR COLOR_RED;
extern const ALLEGRO_COLOR COLOR_GREY;
extern const ALLEGRO_COLOR COLOR_GREEN;
extern const ALLEGRO_COLOR COLOR_YELLOW;
extern const ALLEGRO_COLOR COLOR_BLACK;
extern const ALLEGRO_COLOR COLOR_WHITE;
extern const ALLEGRO_COLOR COLOR_PINK;
extern const ALLEGRO_COLOR COLOR_MAGENTA;
extern const ALLEGRO_COLOR COLOR_BLUE;

//Font
extern int FONT_SIZE;
extern ALLEGRO_FONT *font;

class Drawable {
 protected:
  Drawable()                            = default;
  Drawable(const Drawable &)            = default;
  Drawable(Drawable &&)                 = default;
  Drawable &operator=(const Drawable &) = default;
  Drawable &operator=(Drawable &&)      = default;

 public:
  virtual bool contains(Point p) const = 0;
  virtual void draw()                 = 0;
  virtual ~Drawable()                 = default;
};
// Classes that are going to be used in the application
class Text: public virtual Drawable {
  string        s_;
  Point         center_;
  ALLEGRO_COLOR color_;

 public:
  // Constructor
  Text(string text, Point center, ALLEGRO_COLOR color = COLOR_BLACK);

  // Draw
  void draw() override;

  // Setters and getters
  string getString();
  void   setString(const string &newString);
  Point  getCenter();
  void   setCenter(Point newCenter);
  bool   contains(Point p) const override;
};

class Rectangle : public virtual Drawable { 
protected:
  Point center_;
  float         w_, h_;
  ALLEGRO_COLOR frameColor_, fillColor_;

public:
  Rectangle(Point center, float w, float h,
            ALLEGRO_COLOR frameColor = COLOR_BLACK,
            ALLEGRO_COLOR fillColor  = COLOR_WHITE) noexcept;
  void                draw() override;
  void                setFillColor(ALLEGRO_COLOR newFillColor);
  void                setFrameColor(ALLEGRO_COLOR newFrameColor);
  [[nodiscard]] bool  contains(Point point) const override;
  [[nodiscard]] Point getCenter() const;
};

class Circle : public virtual Drawable {
  Point         center_;
  float         r_;
  ALLEGRO_COLOR frameColor_, fillColor_;

 public:
  Circle(Point center, float r, ALLEGRO_COLOR frameColor = COLOR_BLACK,
         ALLEGRO_COLOR fillColor = COLOR_WHITE) noexcept;
  void                draw() override;
  void                setFillColor(ALLEGRO_COLOR newFillColor);
  void                setFrameColor(ALLEGRO_COLOR newFrameColor);
  [[nodiscard]] bool  contains(Point point) const override;
  [[nodiscard]] Point getCenter() const;
};

/*--------------------------------------------------
TextRectangle
--------------------------------------------------*/
class TextRectangle : public Text, public Rectangle {
 protected:
  TextRectangle(const TextRectangle &)            = default;
  TextRectangle(TextRectangle &&)                 = default;
  TextRectangle &operator=(const TextRectangle &) = default;
  TextRectangle &operator=(TextRectangle &&)      = default;

 public:

  TextRectangle(Point center, float w, float h, string text);
  void draw() override;
  bool contains(Point p) const override;
  ~TextRectangle() override = default;
};

/*--------------------------------------------------
IntRectangle
--------------------------------------------------*/
class IntRectangle : public TextRectangle, public virtual Subject {
  int  theInteger = 0;
  void update();

 protected:
  IntRectangle(const IntRectangle &)            = default;
  // IntRectangle(IntRectangle &&)                 = default;
  IntRectangle &operator=(const IntRectangle &) = default;
  // IntRectangle &operator=(IntRectangle &&)      = default;

 public:
  IntRectangle(IntRectangle&&) = delete;
  IntRectangle& operator=(IntRectangle&&) = delete;
  IntRectangle(Point center, float w, float h, int theInteger);
       operator int() const;
  int  getInteger() const;
  void setInteger(int newInteger);
  ~IntRectangle() override = default;
};

#endif //DRAWABLES_HPP