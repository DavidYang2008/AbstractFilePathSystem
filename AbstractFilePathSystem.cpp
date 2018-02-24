#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>

// Problem 1
class Path
{
	
public:
	Path(std::string path)
	{
		currentPath = path;
	}
	
	std::string getPath() const
	{
		return currentPath;
	}
	
	void setPath(std::string newPath)
	{
		currentPath=newPath;
	}
	
	// solution 1
	// Instead of recursive method, use an iterative
	// solution which could be faster. The idea is the same,
	// treat cd command as a series of command and handle
	// them one at a time
	Path cd_iter(std::string newPath) const {
		Path path(currentPath);
		
		while (!newPath.empty()) {
			if (newPath[0]=='/') {
				
				// case 1: start with "/"
				path.setPath("/");
				// remove "/"
				newPath.erase(0,1);
				
			} else if (newPath.find_first_of("..")==0) {
				
				// case 3: start with ".."
				
				// move directory path one level up
				std::string upperPath=path.up();
				path.setPath(upperPath);
				
				// remove ".."
				newPath.erase(0,2);
				
				if (!newPath.empty()) {
					// remove '/'
					newPath.erase(0,1);
				}
			} else {
				// case 4: start with a directory name "x/"
				auto p=newPath.find_first_of('/');
				path.setPath(path.appendToCurrent(newPath.substr(0, p)));
				
				// remove the directory name
				newPath.erase(0,p);
				if (p!=std::string::npos)
					// erase '/'
					newPath.erase(0, 1);
			}
			
		}
		return path;
		
	}

	// solution 2
	// this function use recursive algorithm to parse a
	// cd path command and create the result path at each step
	Path cd(std::string newPath) const
	{
		// case 1: newPath=="", do not change the path
		if (newPath.empty()) return Path(currentPath);
		
		// case 2: start with "/"
		if (newPath[0]=='/')
			return Path("/").cd(newPath.substr(1));
		
		// case 3: start with ".."
		if (newPath.find_first_of("..")==0) {
			
			// move directory path one level up
			std::string upperPath=up();
			
			if (newPath.size()==2) {
				return Path(upperPath);
			} else {
				//newPath[3]=='/';
				return Path(upperPath).cd(newPath.substr(3));
			}
		}
		
		// case 4: start with a directory name "x/"
		auto p=newPath.find_first_of('/');
		Path path(appendToCurrent(newPath.substr(0, p)));
		if (p!=std::string::npos)
			return path.cd(newPath.substr(p+1));
		else
			return path;
	}
	
	std::string appendToCurrent(const std::string& str) const {
		if (currentPath.back()=='/')
			return currentPath + str;
		else
			return currentPath + "/" + str;
	}
	
	std::string up(void) const {
		auto p=currentPath.find_last_of('/');
		if (p==0)
			return "/";
		else
			return currentPath.substr(0, p);
	}
	
private:
	std::string currentPath;
};

// test helper
void check_result(const std::string& act, const std::string& exp) {
	if (act == exp) {
		std::cout << "Pass!" << std::endl;
	} else {
		std::cout << "Fail: " << act << " != " << exp << std::endl;
	}
}

int main(int argc, const char* argv[])
{
	// test for problem 1
	try {
		std::cout << "testing problem 1" << std::endl;
		// case 0
		{
			Path path("/a/b/c/d");
			check_result(path.cd("../x").getPath(), "/a/b/c/x");
			check_result(path.cd_iter("../x").getPath(), "/a/b/c/x");
		}
		// case 1
		{
		Path path("/");
			check_result(path.cd("../x/../////x/../../////y").getPath(), "/y");
			check_result(path.cd_iter("../x/../////x/../../////y").getPath(), "/y");
		}
		
		// case 2
		{
			Path path("/");
			check_result(path.cd("x").getPath(), "/x");
			check_result(path.cd_iter("x").getPath(), "/x");
		}
		
		// case 3
		{
			Path path("/abc/def");
			check_result(path.cd("/x").getPath(), "/x");
			check_result(path.cd_iter("/x").getPath(), "/x");
		}
		
		// case 4
		{
			Path path("/abc/def/ghi");
			check_result(path.cd("../x").getPath(), "/abc/def/x");
			check_result(path.cd_iter("../x").getPath(), "/abc/def/x");
		}
		
		// case 5
		{
			Path path("/abc/def/ghi");
			check_result(path.cd("../../x").getPath(), "/abc/x");
			check_result(path.cd_iter("../../x").getPath(), "/abc/x");
		}
		
		// case 6
		{
			Path path("/");
			check_result(path.cd("/y/z/../x").getPath(), "/y/x");
			check_result(path.cd_iter("/y/z/../x").getPath(), "/y/x");
		}
		
		// case 7
		{
			Path path("/abc");
			check_result(path.cd("y/z/..//////x/y").getPath(), "/x/y");
			check_result(path.cd_iter("y/z/..//////x/y").getPath(), "/x/y");
		}
		
		// case 8
		{
			Path path("/");
			check_result(path.cd("xyz/abc/../a/b/c/../").getPath(), "/xyz/a/b");
			check_result(path.cd_iter("xyz/abc/../a/b/c/../").getPath(), "/xyz/a/b");
		}
		
		// case 9
		{
			Path path("/");
			check_result(path.appendToCurrent("xyz"), "/xyz");
		}
		
		// case 10
		{
			Path path("/abc");
			check_result(path.appendToCurrent("xyz"), "/abc/xyz");
		}
		
		// case 11
		{
			Path path("/abc");
			check_result(path.up(), "/");
		}
		
		// case 12
		{
			Path path("/abc/xyz");
			check_result(path.up(), "/abc");
		}
		
		// case 13
		{
			Path path("/");
			check_result(path.up(), "/");
		}
		
		// case 13
		{
			Path path("/");
			check_result(path.cd("/x/y/z/").getPath(), "/x/y/z");
			check_result(path.cd_iter("/x/y/z/").getPath(), "/x/y/z");
		}
	} catch (const char* msg) {
		std::cout << msg << std::endl;
	}
	return 0;

}
