#ifndef TWOBEAMALGORITHM_H_
#define TWOBEAMALGORITHM_H_
#include "Algorithm.h"
#include <utility>
/**
\brief Realization of Two Beam Algorithm
*/
class TwoBeamAlgorithm : public Algorithm
{

protected:
	/**
	\brief possible directions of the algorithm
	*/
	enum class Direction {
		UP,
		LEFT,
		RIGHT,
		DOWN
	};
	bool isPath = false; ///< is the path found
	/**
	\brief defines the next point
	\param currentPoint current point
	\return next point
	*/
	Point* interestedNeighbour(Point& currentPoint, const Direction dir_);
private:
	bool alpha{},///< 0 if starting point to the left of the end point, otherwise 1
		beta{};///< 0 if starting point to the up of the end point, otherwise 1		
	/**
	\brief method checks if the specified direction is a path
	\param startPoint_ starting point of verification
	\param mainDir_ mainstream
	\param subDir_ direction, when blocking the main
	*/
	bool isItCorrectDirect(Point*const startPoint_,const Direction mainDir_,const Direction subDir_);
	/**
	\brief method build result path on one direction
	\param startPoint_ starting point
	\param mainDir_ mainstream
	\param subDir_ direction, when blocking the main
	*/
	void buildPath(Point*const startPoint_,const Direction mainDir_,const Direction subDir_);
	/**
	\brief path building method on one direction
	\param startPoint_ starting point
	\param mainDir_ mainstream
	\param subDir_ direction, when blocking the main
	*/
protected:
	void buildWay(Point*const startPoint_,const Direction mainDir_,const Direction subDir_);
public:
	/**
	\brief path building method
	\param pointList point list
	\return true if it was possible to build a path, otherwise false
	*/
	virtual bool buildPath(std::vector<Point>& pointList) override;
	/**
	\brief path finding method
	\param pointList point list
	*/
	virtual void findPath(std::vector<Point>& pointList) override;
	
	
	virtual ~TwoBeamAlgorithm() = default;

};
#endif // !TWOBEAMALGORITHM_H_