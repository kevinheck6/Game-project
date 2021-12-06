#pragma once

class AnimationComponent {
private:
	class Animation {
	public:
		//Variables
		sf::Sprite& sprite;
		sf::Texture& textureAnimation;
		float timeAnimation;
		float time;
		bool finished;
		int width;
		int height;
		sf::IntRect startRe;
		sf::IntRect currentRe;
		sf::IntRect endRe;

		Animation(sf::Sprite& sprite, sf::Texture& texture_sheet, 
			float animation_timer, 
			int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height)
			: sprite(sprite), textureAnimation(texture_sheet),
              timeAnimation(animation_timer), time(0.f), finished(false),
              width(width), height(height) {

			this->startRe = sf::IntRect(start_frame_x * width,
                                          start_frame_y * height,
                                        width, height);
			this->currentRe = startRe;
			this->endRe = sf::IntRect(frames_x * width,
                                        frames_y * height,
                                      width, height);

			this->sprite.setTexture(textureAnimation, true);
			this->sprite.setTextureRect(startRe);
		}

		//Accessor
		const bool& isDone() const {
			return finished;
		}

		//Functions
		const bool& play(const float& dt) {

			finished = false;
            time += 100.f * dt;
			if (time >= timeAnimation) {
				//reset the time
				time = 0.f;

				//Animate
				if (currentRe != endRe) {
                    currentRe.left += width;
				} else { //end it
					currentRe.left = startRe.left;
                    finished = true;
				}
				sprite.setTextureRect(currentRe);
			}
			return finished;
		}

		const bool& play(const float& dt, float mod_percent) {
			//Update time
			if (mod_percent < 0.5f) {
                mod_percent = 0.5f;
            }

            finished = false;
            time += mod_percent * 100.f * dt;
			if (time >= timeAnimation) {
				//reset time
				time = 0.f;

				//Animate
				if (currentRe != endRe) {
                    currentRe.left += width;
				} else { //Reset
					currentRe.left = startRe.left;
                    finished = true;
				}
				sprite.setTextureRect(currentRe);
			}
			return finished;
		}

		void reset() {
            time = timeAnimation;
            currentRe = startRe;
		}
	};

	sf::Sprite& sprite;
	sf::Texture& texture;
	std::map<std::string, Animation*> animations;
	Animation* lastAnimation;
	Animation* priorityAnimation;

public:
    //Constructor
	AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet);
    //Destructor
	virtual ~AnimationComponent();

	//Functions
	void addAnimation(const std::string& key,
		float animation_timer,
		int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height);

	const bool& play(const std::string& key, const float& dt, bool priority = false);
	const bool& play(const std::string& key, const float& dt, const float& modifier,
                     const float& modifier_max, bool priority = false);
};

