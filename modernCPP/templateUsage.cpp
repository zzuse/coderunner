#include <iostream>
#include <map>

using namespace std;

struct Mat{
public:
	std::string filename;
	Mat(std::string _filename):filename(_filename)
	{
	};
};

class ImagesPool {
	public:
		std::map<std::string, Mat> pre_alloc_images_map;
		std::mutex mtx;
		~ImagesPool()
		{
			if (pre_alloc_images_map.size() > 0) {
				pre_alloc_images_map.clear();
			}
		}
};
ImagesPool image_pool;

int main(int argc, char *argv[]) {
	std::string filename = "123";
	std::lock_guard<std::mutex> lk(image_pool.mtx);
	auto it = image_pool.pre_alloc_images_map.find(filename);
	if (it == image_pool.pre_alloc_images_map.end()) {
		Mat a(filename);
		image_pool.pre_alloc_images_map.emplace(filename, a);
	}
}