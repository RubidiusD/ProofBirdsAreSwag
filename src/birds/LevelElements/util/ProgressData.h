#ifndef BIRDSARESWAG_PROGRESS_DATA_H
#define BIRDSARESWAG_PROGRESS_DATA_H

#include <SFML/System/String.hpp>
#include <cmath>
#include <string>
#include <vector>

enum ProgressType {
  UNFINISHED,
  DIED,
  WON,
  QUIT
};

struct Chapter {
  ProgressType type = UNFINISHED; // made
  unsigned progress = 0; // made
  float duration = 0.0f; // made
  unsigned times_hit = 0; // made
  unsigned times_missed = 0;
  float time_spent_counter_steering = 0.0f; // made
  unsigned times_jumped = 0; // made
  unsigned times_coyoted = 0; // made
  unsigned times_bounced = 0;
  unsigned times_stuck = 0;
  float first_egg = -1.0f;
  float second_egg = -1.0f;

  Chapter(unsigned p, float d, unsigned h, unsigned m, float s, unsigned j, unsigned c, unsigned b, unsigned l, ProgressType t) {
    progress = p;
    duration = d;
    times_hit = h;
    times_missed = m;
    time_spent_counter_steering = s;
    times_jumped = j;
    times_coyoted = c;
    times_bounced = b;
    times_stuck = l;
    type = t;
  }

  Chapter() = default;

  Chapter& operator+=(const Chapter& rhs) {
    type = rhs.type;
    progress = rhs.progress;
    duration += rhs.duration;
    times_hit += rhs.times_hit;
    times_missed = rhs.times_missed;
    time_spent_counter_steering += rhs.time_spent_counter_steering;
    times_jumped += rhs.times_jumped;
    times_coyoted += rhs.times_coyoted;
    times_bounced += rhs.times_bounced;
    times_stuck += rhs.times_stuck;
    return *this;
  }

  void reset() {
    type = UNFINISHED;
    progress = 0;
    duration = 0.0f;
    times_hit = 0;
    time_spent_counter_steering = 0.0f;
    times_jumped = 0;
    times_coyoted = 0;
    times_bounced = 0;
    times_stuck = 0;
  }
};

struct Attempt : public Chapter {
  std::vector<Chapter> chapters;

  sf::String look_nice() const {
    int minutes = (int)floorf(duration / 60.0f);
    int seconds = (int)floorf(duration - (float)minutes);
    std::string minutes_string = std::to_string(minutes);
    std::string seconds_string = std::to_string(seconds);
    std::string milliseconds_string = std::to_string((int)floorf((duration - (float)minutes - float(seconds)) * 1000.0f));
    while (seconds_string.length() != 2) seconds_string = "0" + seconds_string;
    while (milliseconds_string.length() != 3) milliseconds_string = "0" + milliseconds_string;

    return minutes_string + ":" + seconds_string + "." + milliseconds_string;
  }

  Attempt() = default;

  void AddChapter(const Chapter& chapter) {
    chapters.emplace_back(chapter);
    operator+=(chapter);
  }
};

#endif // BIRDSARESWAG_PROGRESS_DATA_H
