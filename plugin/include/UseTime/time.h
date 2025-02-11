struct time {
    int hour;
    int minute;
    int second;
};

struct time secondToTime(double second) {
	int hr = (int) (second / 3600);

	second = fmod(second, 3600);

	int min = (int) (second / 60);

	second = fmod(second, 60);

	int sec = (int)(second);

	struct time result = {
		hr,
		min,
		sec
	};

	return result;
}