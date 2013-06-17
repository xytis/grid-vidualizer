
#include "CGrid.h"

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cassert>

CGrid::CGrid(int w, int h)
: _w(w)
, _h(h)
{
    _grid.resize(w);
    for (int i = 0; i < w; ++i) {
        _grid[i].resize(h);
    }
}

void CGrid::draw()
{
    
    float scale = 5.0f / std::max(_w, _h);
    glScalef(scale, scale, scale);
    glTranslatef(-(float)(_w - 1) / 2,
                 -(float)(_h - 1) / 2,
                 0.0f);
   
     /// For each cell render a quad.
    for(int x = 0; x < _w; ++x) {
        for(int y = 0; y < _h; ++y) {
            switch (_grid[x][y].state) {
                case SElement::Free:
                    glColor3f(0.1f,0.7f,0.2f);
                    break;
                case SElement::Occupied:
                    glColor3f(0.7f,0.1f,0.2f);
                    break;
                default:
                    glColor3f(0.3f,0.3f,0.3f);
                    break;
            }
            glBegin(GL_QUADS);                      // Draw A Quad
            glNormal3f(0.0f, 0.0f, 1.0f);
            glVertex3f(x-0.5f, y+0.5f, 0.0f);              // Top Left
            glVertex3f(x+0.5f, y+0.5f, 0.0f);              // Top Right
            glVertex3f(x+0.5f, y-0.5f, 0.0f);              // Bottom Right
            glVertex3f(x-0.5f, y-0.5f, 0.0f);              // Bottom Left
            glEnd();                            // Done Drawing The Quad
        }
    }
    /// Render all links.
    for(int x = 0; x < _w; ++x) {
        for(int y = 0; y < _h; ++y) {
            for(int n = 0; n < Direction::_cnt; ++n) {
                switch (_grid[x][y].neighbours[n]) {
                    case SElement::None:
                    glColor3f(0.3f,0.3f,0.3f);
                    break;
                case SElement::InQueue:
                    glColor3f(0.5f,0.5f,0.2f);
                    break;
                case SElement::NextInLine:
                    glColor3f(0.5f,0.5f,0.2f);
                    break;
                case SElement::Checked:
                    glColor3f(0.2f,0.2f,0.7f);
                    break;
                case SElement::InPath:
                    glColor3f(0.3f,0.9f,0.2f);
                    break;
                default:
                    glColor3f(0.3f,0.3f,0.3f);
                    break;
                }
                if ((x + Direction::map[n][0] > -1 && x + Direction::map[n][0] < _w) && (y + Direction::map[n][1] > -1 && y + Direction::map[n][1] < _h)) {
                glLineWidth(2.5); 
                glBegin(GL_LINES);
                glVertex3f(x, y, 0.1f);
                glVertex3f(x + Direction::map[n][0], y + Direction::map[n][1], 0.1f);
                glEnd();
                }
            }
        }
    }
}

void CGrid::link(int x, int y, Direction::EDirection direction, SElement::PathState state)
{
    assert(x < _w && y < _h);
    assert(direction < Direction::_cnt);
    _grid[x][y].neighbours[direction] = state;
}

void CGrid::set(int x, int y, SElement::ElementState state)
{
    assert(x < _w && y < _h);
     _grid[x][y].state = state;
}
