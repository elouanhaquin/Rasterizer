RASTERIZER

###Rasterizer
2017's school project. Rasterizer made from scratch.

###Screenshot
![](https://i.ibb.co/TM7QGPs/rasterizer.png)


Team : Enzo Fusco - Elouan Haquin - Quentin Stawarz

V0

Vec3 :
	- float x, y, z;		// Coordinates for vector in 3D space
	- float GetMagnitude() const; 	// Return the magnitude of the vector
	- void Normalize();		// Normalize the vector
	- operator+(Vec3, Vec3);	// Operator + to additionate two vectors Vec3
	- operator*(Vec3, float);	// Operator * to scale a vector Vec3 with a scalar

Vec4 :
	- float x, y, z, w;				// Homogeneous coordinates for vector in 3D space
	- void Homogenize();				// Homogenize the vector (divide the coordinates by w, w != 0)
	- float GetMagnitude() const;			// Return the magnitude of the homogeneous vector
	- void Normalize();				// Normalize the homogeneous vector
	- operator+(Vec4, Vec4);			// Operator + to add two vectors Vec4
	- operator*(Vec4, float);			// Operator * to scale a vector Vec4 with a scalar
	- Vec4(const Vec3& vec3, float w = 1.0f);	// Contructor to construct a vector Vec4 with a vector Vec3 and/or
							// a w to homogenize the vector (default 1.0f)

Mat4 :
	- float data[4][4];						// Two dimensional arrays for elements of a matrix 4x4
	- operator*(Mat4, Mat4);					// Operator * to multiply two matrices Mat4
	- operator*(Mat4, Vec4);					// Operator * to multiply a matrix Mat4 and a vector Vec4
	- static Mat4 CreateTransformMatrix(const Vec3& rotation,
					    const Vec3& position,
					    const Vec3& scale);		// Create a transform matrix, the rotation vector contain
									// angles in degrees
	- static Mat4 CreateTranslationMatrix(const Vec3& translation);	// Create a translate matrix to calculate the transform matrix
	- static Mat4 CreateScaleMatrix(const Vec3& scale);		// Create a scale matrix to calculate the transform matrix
	- static Mat4 CreateXRotationMatrix(float angle);		// Create a rotation matrix on x axis to calculate the transform matrix
	- static Mat4 CreateYRotationMatrix(float angle);		// Create a rotation matrix on y axis to calculate the transform matrix
	- static Mat4 CreateZRotationMatrix(float angle);		// Create a rotation matrix on z axis to calculate the transform matrix

Vertex :
	- Vec3 position;	// Coordinates for vertex in 3D space

Mesh :
	- std::vector<Vertex> vertices;				// Vertices container of the mesh (doesn't change, but the transform matrix does)
	- std::vector<int> indices;				// Indices container to determine triangles of the mesh (3 consecutive index is a triangle)
	- static Mesh* CreateCube();				// Create a cube with a size of 1, 8 vertices and 36 indices (12 triangles)
	- static Mesh* CreateSphere(int latitudeCount,
				    int longitudeCount);	// Create a sphere with a radius of 1, vertices and indices are determine by
								// the given latitudeCount and longitudeCount

Color :
	- unsigned char r, g, b, a;	// Elements to determine the color and the alpha (ranges from 0 to 255)

Texture :
	- unsigned int width, height;		// Width and height of the texture, determine the size of the pixel array
	- Color* pixel;				// Array for elements of a texture (each element is a pixel)
	- Texture(unsigned int width, height);	// Constructor to construct a texture with the width and the height (no default constructor)
	- void SetPixelColor(unsigned int x,
			     unsigned y,
			     const Color& c);	// Set the color of the pixel at the given index x, y

Entity :
	- Mesh* mesh;		// Pointer to a mesh that is the instance of the mesh on the screen (the same mesh can be use without duplicate values)
	- Mat4 transform;	// Transform matrix to rotate, translate and/or scale the mesh

Scene :
	- std::vector<Entity> entities;		// Entities container of the scene (elements on the screen)
	- ~Scene();				// Destructor of the scene, must destroy all the elements of the scene (entities / meshs)

Rasterizer :
	- void RenderScene(Scene* pScene, Texture* pTarget);	// Render the scene in the 3D texture
