#pragma once

struct Renderer2DStatistics
{
	long DrawCount = 0 ;
	long QuadCount = 0;
	long GetVertexCount(){ return QuadCount * 4; }
	long GetIndexCount(){ return QuadCount * 6; }
	void Reset() { memset(this, 0, sizeof(Renderer2DStatistics)); }
};