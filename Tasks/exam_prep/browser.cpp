#include <iostream>

// Create a class representing a Browser. The browser allows visiting a page
// using a given URL (string), moving backward through the history of visited
// pages, and moving forward again. You must support the following interface:
//
// Constructor taking homeUrl (string) – the web address of the browser's home page.
//
// Function visit, taking url (string) – the current page becomes a previous page
// in the history, and the current page becomes the one given by the URL.
//
// Function back, taking steps (unsigned int) – the number of steps to go back
// in the history (if the number of steps is more than possible – we go back to home).
// After moving, the function returns the URL of the page we have reached.
//
// Function forward, taking steps (unsigned int) – the number of steps to go forward
// in the history (if the number of steps is more than possible – we go to the
// most recently visited page). After moving, the function returns the URL of
// the page we have reached.
//
// Function getCurrent, which returns the URL of the current page.
//
// Function reset, which returns us to the home page and clears the entire history.


class Browser {
	struct Node {
		std::string url;
		Node* next = nullptr;
		Node* prev = nullptr;

		Node(const std::string str):url(str){}
	};
public:
	Browser(const std::string& homePage) {
		head = currNode = new Node(homePage);
	}

    void visit(const std::string& url){
        if (currNode->next){
            free(currNode->next);
        }

        currNode->next = new Node(url);
        currNode->next->prev = currNode;
        currNode = currNode->next;
    }

    const std::string& back(unsigned int steps){
        while (currNode->prev != nullptr && steps != 0){
            currNode = currNode->prev;
            steps--;
        }
        return currNode->url;
    }

    const std::string& forward(unsigned int steps){
        while (currNode->next != nullptr && steps != 0){
            currNode = currNode->next;
            steps--;
        }
        return currNode->url;
    }

    void reset(){
        currNode = head;
        free(head->next);
        head->next = nullptr;
    }

    const std::string& getCurrent() const{
        return currNode->url;
    }

    Browser(const Browser&) = delete;
    Browser& operator=(const Browser&) = delete;

private:
	Node* head = nullptr;
	Node* currNode = nullptr;

	void free(Node* nodePtr) {
		while (nodePtr) {
			Node* temp = nodePtr->next;
			delete nodePtr;
			nodePtr = temp;
		}
	}
};