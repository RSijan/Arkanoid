#include "drawables.hpp"

#include <string>


const ALLEGRO_COLOR COLOR_RED     = al_map_rgb(255, 0, 0);
const ALLEGRO_COLOR COLOR_GREY    = al_map_rgb(200, 200, 200);
const ALLEGRO_COLOR COLOR_GREEN   = al_map_rgb(0, 255, 0);
const ALLEGRO_COLOR COLOR_YELLOW  = al_map_rgb(255, 255, 0);
const ALLEGRO_COLOR COLOR_BLACK   = al_map_rgb(0, 0, 0);
const ALLEGRO_COLOR COLOR_WHITE   = al_map_rgb(255, 255, 255);
const ALLEGRO_COLOR COLOR_PINK    = al_map_rgb(200, 150, 167);
const ALLEGRO_COLOR COLOR_MAGENTA = al_map_rgb(255, 0, 255);
const ALLEGRO_COLOR COLOR_BLUE    = al_map_rgb(0, 0, 255);

// Global that contains font size and the font itself
int     FONT_SIZE = 20;
ALLEGRO_FONT *font=nullptr;

// Implementation for Text
Text::Text(string text, Point center, ALLEGRO_COLOR color)
      : s_{text}, center_{center}, color_{color} {}

void Text::draw() {
  auto verticalCenterAdjustment =
      static_cast<float>(al_get_font_line_height(font) / 2.0);
  al_draw_text(font, color_, center_.x, center_.y - verticalCenterAdjustment,
               ALLEGRO_ALIGN_CENTRE, s_.c_str());
}

string Text::getString() { return s_; }
void   Text::setString(const string &newString) { s_ = newString; }
Point  Text::getCenter() { return center_; }
void   Text::setCenter(Point newCenter) { center_ = newCenter; }

bool   Text::contains(Point p) const {
    auto w=al_get_font_line_height(font);
    auto h=al_get_text_width(font,s_.c_str());
    auto verticalCenterAdjustment = 
        static_cast<float>(al_get_font_line_height(font) / 2.0);
    return abs(p.x-center_.x)<=w && abs(p.y-(center_.y - verticalCenterAdjustment))<=h;
}


// Implementation for Rectangle
Rectangle::Rectangle(Point center, float w, float h, ALLEGRO_COLOR frameColor,
                     ALLEGRO_COLOR fillColor) noexcept
    : center_{center},
      w_{w},
      h_{h},
      frameColor_{frameColor},
      fillColor_{fillColor} {}

void Rectangle::draw() {
  const float x1 = center_.x - w_ / 2;
  const float x2 = center_.x + w_ / 2;
  const float y1 = center_.y - h_ / 2;
  const float y2 = center_.y + h_ / 2;
  al_draw_filled_rectangle(x1, y1, x2, y2, fillColor_);
  al_draw_rectangle(x1, y1, x2, y2, frameColor_, 1);
}

void Rectangle::setFillColor(ALLEGRO_COLOR fillColor) {
  fillColor_ = fillColor;
}

void Rectangle::setFrameColor(ALLEGRO_COLOR frameColor) {
  frameColor_ = frameColor;
}

bool Rectangle::contains(Point point) const {
  return point.x >= center_.x - w_ / 2 && point.x < center_.x + w_ / 2 &&
         point.y >= center_.y - h_ / 2 && point.y < center_.y + h_ / 2;
}

Point Rectangle::getCenter() const { return center_; }


// Implementation for Circle
Circle::Circle(Point center, float r, ALLEGRO_COLOR frameColor,
               ALLEGRO_COLOR fillColor) noexcept
    : center_{center}, r_{r}, frameColor_{frameColor}, fillColor_{fillColor} {}

void Circle::draw() {
  al_draw_filled_circle(center_.x, center_.y, r_, fillColor_);
  al_draw_circle(center_.x, center_.y, r_, frameColor_, 1);
}

void Circle::setFillColor(ALLEGRO_COLOR fillColor) { fillColor_ = fillColor; }

void Circle::setFrameColor(ALLEGRO_COLOR frameColor) {
  frameColor_ = frameColor;
}

Point Circle::getCenter() const { return center_; }

bool Circle::contains(Point p) const {
  return ((p.x - center_.x) * (p.x - center_.x) +
              (p.y - center_.y) * (p.y - center_.y) <=
          r_ * r_);
}


// Implementation for TextRectangle
TextRectangle::TextRectangle(Point center, float w, float h, string text)
    : Text{text, center}, Rectangle{center, w, h} {}

void TextRectangle::draw() {
  Rectangle::draw();
  Text::draw();
}

bool TextRectangle::contains(Point p) const { return Rectangle::contains(p); }


// Implementation for IntRectangle
void IntRectangle::update() {
    setString(to_string(theInteger));
    notifyObservers();
}

IntRectangle::IntRectangle(Point center, float w, float h, int theInteger)
      : TextRectangle{center, w, h, ""}, theInteger{theInteger} {
    update();
}
int  IntRectangle::getInteger() const { return theInteger; }
void IntRectangle::setInteger(int newInteger) {
    theInteger = newInteger;
    update();
}