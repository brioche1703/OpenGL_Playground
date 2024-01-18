#include "Buffer.h"

namespace Playground
{

Buffer::Buffer()
{
    glGenBuffers(1, &_id);
}
void Buffer::Bind(GLenum target)
{
    glBindBuffer(target, _id);
}
void Buffer::Data(GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage)
{
    glBufferData(target, size, data, usage);
}
void Buffer::Delete()
{
    glDeleteBuffers(1, &_id);
}
} // namespace Playground
