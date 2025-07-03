#pragma once

#include "colour.hpp"

class GraphicsUtility {
public: // Properties

private: // Member Variables

protected:
	GraphicsUtility() = default;
	
public: // Public Functions
	virtual ~GraphicsUtility() = default;

	GraphicsUtility(const GraphicsUtility&) = delete;
	GraphicsUtility(GraphicsUtility&&) = delete;
	GraphicsUtility& operator=(const GraphicsUtility&) = delete;

	virtual void clear(const Colour& colour) = 0;


	virtual void startRendering() = 0;
	virtual void stopRendering() = 0;

private: // Private Methods
};
