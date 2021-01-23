//
//  glShape.cpp
//  OpenGL Application
//
//  Created by Cellyceos on 29/01/2014.
//  Copyright (c) 2014 Kirill Bravichev. All rights reserved.
//

#include "../include/glShape.h"

glShape::glShape(GLuint numVertices, GLuint numIndices) : tangents(nullptr), vertices(nullptr), normals(nullptr), texCoords(nullptr), vertexCount(numVertices), indexCount(numIndices) {
	normals = new Vector3f[vertexCount];
	tangents = new Vector3f[vertexCount];
	vertices = new Vector3f[vertexCount];
	texCoords = new Vector2f[vertexCount];

	indices = new GLuint[indexCount];
}

glShape* glShape::CreateCube(const GLfloat height, GLuint numberSlices) {
	/*GLuint numberParallels = numberSlices;
	GLuint numberVertices = (numberParallels + 1) * (numberSlices + 1) * 6;
	GLuint numberIndices = numberParallels * numberSlices * 6 * 6;

	glShape* shape = new glShape(numberVertices, numberIndices);

	GLfloat ParallelsStep = height / numberParallels;
	GLfloat SlicesStep = height / numberSlices;
	GLfloat halfHeight = height / 2.0f;
	GLuint indexIndices = 0;

	for (GLuint n = 0; n < 6; n++) {
		for (GLuint i = 0; i <= numberParallels; i++) {
			for (GLuint j = 0; j <= numberSlices; j++) {
				GLuint index = (i * (numberSlices + 1) + j);

				shape->vertices[index] = Vector3f(halfHeight - j * ParallelsStep, 0.0f, halfHeight - i * SlicesStep);
				shape->normals[index] = Vector3f(0.0f, 1.0f, 0.0f);
				shape->texCoords[index] = Vector2f((GLfloat)j / (GLfloat)numberSlices, 1.0f - (GLfloat)i / (GLfloat)numberParallels);
			}
		}

		for (GLuint i = 0; i < numberParallels; i++) {
			for (GLuint j = 0; j < numberSlices; j++) {
				shape->indices[indexIndices++] = i * (numberSlices + 1) + j;
				shape->indices[indexIndices++] = (i + 1) * (numberSlices + 1) + j;
				shape->indices[indexIndices++] = (i + 1) * (numberSlices + 1) + (j + 1);

				shape->indices[indexIndices++] = i * (numberSlices + 1) + j;
				shape->indices[indexIndices++] = (i + 1) * (numberSlices + 1) + (j + 1);
				shape->indices[indexIndices++] = i * (numberSlices + 1) + (j + 1);
			}
		}
	}*/

	Vector3f vertices[] = {
		Vector3f(-height, -height, -height), Vector3f(-height, -height, +height),
		Vector3f(+height, -height, +height), Vector3f(+height, -height, -height),

		Vector3f(-height, +height, -height), Vector3f(-height, +height, +height),
		Vector3f(+height, +height, +height), Vector3f(+height, +height, -height),

		Vector3f(-height, -height, -height), Vector3f(-height, +height, -height),
		Vector3f(+height, +height, -height), Vector3f(+height, -height, -height),

		Vector3f(-height, -height, +height), Vector3f(-height, +height, +height),
		Vector3f(+height, +height, +height), Vector3f(+height, -height, +height),

		Vector3f(-height, -height, -height), Vector3f(-height, -height, +height),
		Vector3f(-height, +height, +height), Vector3f(-height, +height, -height),

		Vector3f(+height, -height, -height), Vector3f(+height, -height, +height),
		Vector3f(+height, +height, +height), Vector3f(+height, +height, -height)
	};

	Vector3f normals[] = {
		Vector3f(0.0f, -1.0f, 0.0f), Vector3f(0.0f, -1.0f, 0.0f), Vector3f(0.0f, -1.0f, 0.0f), Vector3f(0.0f, -1.0f, 0.0f),
		Vector3f(0.0f, +1.0f, 0.0f), Vector3f(0.0f, +1.0f, 0.0f), Vector3f(0.0f, +1.0f, 0.0f), Vector3f(0.0f, +1.0f, 0.0f),
		Vector3f(0.0f, 0.0f, -1.0f), Vector3f(0.0f, 0.0f, -1.0f), Vector3f(0.0f, 0.0f, -1.0f), Vector3f(0.0f, 0.0f, -1.0f),
		Vector3f(0.0f, 0.0f, +1.0f), Vector3f(0.0f, 0.0f, +1.0f), Vector3f(0.0f, 0.0f, +1.0f), Vector3f(0.0f, 0.0f, +1.0f),
		Vector3f(-1.0f, 0.0f, 0.0f), Vector3f(-1.0f, 0.0f, 0.0f), Vector3f(-1.0f, 0.0f, 0.0f), Vector3f(-1.0f, 0.0f, 0.0f),
		Vector3f(+1.0f, 0.0f, 0.0f), Vector3f(+1.0f, 0.0f, 0.0f), Vector3f(+1.0f, 0.0f, 0.0f), Vector3f(+1.0f, 0.0f, 0.0f) };

	Vector2f texCoords[] = {
		Vector2f(0.0f, 1.0f), Vector2f(0.0f, 0.0f), Vector2f(1.0f, 0.0f), Vector2f(1.0f, 1.0f),
		Vector2f(0.0f, 0.0f), Vector2f(0.0f, 1.0f), Vector2f(1.0f, 1.0f), Vector2f(1.0f, 0.0f),
		Vector2f(0.0f, 0.0f), Vector2f(0.0f, 1.0f), Vector2f(1.0f, 1.0f), Vector2f(1.0f, 0.0f),
		Vector2f(1.0f, 0.0f), Vector2f(1.0f, 1.0f), Vector2f(0.0f, 1.0f), Vector2f(0.0f, 0.0f),
		Vector2f(1.0f, 0.0f), Vector2f(0.0f, 0.0f), Vector2f(0.0f, 1.0f), Vector2f(1.0f, 1.0f),
		Vector2f(0.0f, 0.0f), Vector2f(1.0f, 0.0f), Vector2f(1.0f, 1.0f), Vector2f(0.0f, 1.0f) };

	GLuint indices[] = { 0, 2, 1, 0, 3, 2, 4, 5, 6, 4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 15, 14, 12, 14, 13, 16, 17, 18, 16, 18, 19, 20, 23, 22, 20, 22, 21 };

	glShape* shape = new glShape(24u, 36u);

	memcpy(shape->vertices, vertices, sizeof(vertices));
	memcpy(shape->normals, normals, sizeof(normals));
	memcpy(shape->texCoords, texCoords, sizeof(texCoords));
	memcpy(shape->indices, indices, sizeof(indices));

	shape->CalculateTangent();

	return shape;
}

glShape* glShape::CreatePlane(const GLfloat height, GLuint numberSlices) {
	GLuint numberParallels = numberSlices;
	GLuint numberVertices = (numberParallels + 1u) * (numberSlices + 1u);
	GLuint numberIndices = numberParallels * numberSlices * 6u;

	glShape* shape = new glShape(numberVertices, numberIndices);

	GLfloat ParallelsStep = height / numberParallels;
	GLfloat SlicesStep = height / numberSlices;
	GLfloat halfHeight = height / 2.0f;

	for (GLuint i = 0u; i < numberParallels + 1u; i++) {
		for (GLuint j = 0u; j < numberSlices + 1u; j++) {
			GLuint index = (i * (numberSlices + 1u) + j);

			shape->vertices[index] = Vector3f(halfHeight - j * ParallelsStep, 0.0f, halfHeight - i * SlicesStep);
			shape->normals[index] = Vector3f(0.0f, 1.0f, 0.0f);
			shape->texCoords[index] = Vector2f(1.0f - (GLfloat)j / (GLfloat)numberSlices, 1.0f - (GLfloat)i / (GLfloat)numberParallels);
		}
	}

	GLuint indexIndices = 0;
	for (GLuint i = 0u; i < numberParallels; i++) {
		for (GLuint j = 0u; j < numberSlices; j++) {
			shape->indices[indexIndices++] = i * (numberSlices + 1u) + j;
			shape->indices[indexIndices++] = (i + 1u) * (numberSlices + 1u) + j;
			shape->indices[indexIndices++] = (i + 1u) * (numberSlices + 1u) + (j + 1u);

			shape->indices[indexIndices++] = i * (numberSlices + 1u) + j;
			shape->indices[indexIndices++] = (i + 1u) * (numberSlices + 1u) + (j + 1u);
			shape->indices[indexIndices++] = i * (numberSlices + 1u) + (j + 1u);
		}
	}

	shape->CalculateTangent();

	return shape;
}

glShape* glShape::CreateSphere(const GLuint numberSlices, const GLfloat radius) { // количество разрезов на сфере, радиус
	GLuint numberParallels = numberSlices / 2; // кол-во параллелей
	GLuint numberVertices = (numberParallels + 1u) * (numberSlices + 1u); // колв-во вершин
	GLuint numberIndices = numberParallels * numberSlices * 6u; // колв-во индексов

	assert(radius > 0u);
	assert(numberSlices >= 3u);
	assert(numberIndices < MAX_INDICES);
	assert(numberVertices < MAX_VERTICES);

	GLfloat angleStep = M_2PI / numberSlices;

	glShape* shape = new glShape(numberVertices, numberIndices);

	for (GLuint i = 0u; i < numberParallels + 1u; i++) {
		for (GLuint j = 0u; j < numberSlices + 1u; j++) {
			GLuint index = (i * (numberSlices + 1u) + j);

			shape->vertices[index] = Vector3f(radius * sinf(angleStep * (GLfloat)i) * sinf(angleStep * (GLfloat)j), radius * cosf(angleStep * (GLfloat)i), radius * sinf(angleStep * (GLfloat)i) * cosf(angleStep * (GLfloat)j));
			shape->normals[index] = Vector3f(shape->vertices[index].x / radius, shape->vertices[index].y / radius, shape->vertices[index].z / radius);
			shape->texCoords[index] = Vector2f((GLfloat)j / (GLfloat)numberSlices, ((GLfloat)i / numberParallels));
		}
	}

	GLuint indexIndices = 0u;
	for (GLuint i = 0u; i < numberParallels; i++) {
		for (GLuint j = 0u; j < numberSlices; j++) {
			shape->indices[indexIndices++] = i * (numberSlices + 1u) + j;
			shape->indices[indexIndices++] = (i + 1u) * (numberSlices + 1u) + j;
			shape->indices[indexIndices++] = (i + 1u) * (numberSlices + 1u) + (j + 1u);

			shape->indices[indexIndices++] = i * (numberSlices + 1u) + j;
			shape->indices[indexIndices++] = (i + 1u) * (numberSlices + 1u) + (j + 1u);
			shape->indices[indexIndices++] = i * (numberSlices + 1u) + (j + 1u);
		}
	}

	shape->CalculateTangent();

	return shape;
}

glShape* glShape::CreateCone(const GLuint numberSlices, const GLfloat topRadius, const GLfloat buttomRadius, const GLfloat height) {
	const GLuint numberParallels = numberSlices;

	GLuint numberVertices = (numberParallels + 1u) * (numberSlices + 1u) + 2u;
	GLuint numberIndices = numberParallels * numberSlices * 6u;
	numberIndices += topRadius == 0u || buttomRadius == 0u ? numberSlices * 3u : numberSlices * 6u;

	assert(topRadius >= 0u);
	assert(buttomRadius >= 0u);
	assert(numberSlices >= 3u);
	assert(numberIndices < MAX_INDICES);
	assert(numberVertices < MAX_VERTICES);

	GLfloat angleStep = M_2PI / numberSlices;
	GLfloat halfHeight = height / 2.0f;

	glShape* shape = new glShape(numberVertices, numberIndices);

	for (GLuint i = 0u; i < numberParallels + 1u; i++) {
		for (GLuint j = 0u; j < numberSlices + 1u; j++) {
			GLuint index = (i * (numberSlices + 1u) + j);
			GLfloat radius = topRadius + i * (fabsf(buttomRadius - topRadius) / numberParallels);

			shape->vertices[index] = Vector3f(radius * cosf(angleStep * (GLfloat)j), halfHeight - i * (height / numberParallels), radius * sinf(angleStep * (GLfloat)j));
			shape->normals[index] = Vector3f(shape->vertices[index].x / radius, shape->vertices[index].y / radius, shape->vertices[index].z / radius);
			shape->texCoords[index] = Vector2f((GLfloat)j / (GLfloat)numberSlices, 1.0f - (GLfloat)i / (GLfloat)numberParallels);
		}
	}

	GLuint indexIndices = 0u;
	if (topRadius > 0u) {
		shape->vertices[numberVertices - 2u] = Vector3f(0.0f, halfHeight, 0.0f);
		shape->normals[numberVertices - 2u] = Vector3f(0.0f, 1.0f, 0.0f);
		shape->texCoords[numberVertices - 2u] = Vector2f(0.0f, 0.0f);

		for (GLuint i = 0u; i < numberSlices; i++) {
			shape->indices[indexIndices++] = numberVertices - 2u;
			shape->indices[indexIndices++] = i + 1u;
			shape->indices[indexIndices++] = i;
		}
	}

	for (GLuint i = 0u; i < numberParallels; i++) {
		for (GLuint j = 0u; j < numberSlices; j++) {
			shape->indices[indexIndices++] = i * (numberSlices + 1u) + j;
			shape->indices[indexIndices++] = (i + 1u) * (numberSlices + 1u) + (j + 1u);
			shape->indices[indexIndices++] = (i + 1u) * (numberSlices + 1u) + j;

			shape->indices[indexIndices++] = i * (numberSlices + 1u) + j;
			shape->indices[indexIndices++] = i * (numberSlices + 1u) + (j + 1u);
			shape->indices[indexIndices++] = (i + 1u) * (numberSlices + 1u) + (j + 1u);
		}
	}

	if (buttomRadius > 0u) {
		shape->vertices[numberVertices - 1u] = Vector3f(0.0f, -halfHeight, 0.0f);
		shape->normals[numberVertices - 1u] = Vector3f(0.0f, -1.0f, 0.0f);
		shape->texCoords[numberVertices - 1u] = Vector2f(1.0f, 1.0f);

		for (GLuint i = 0u; i < numberSlices; i++) {
			shape->indices[indexIndices++] = numberParallels * (numberSlices + 1u) + (i + 1u);;
			shape->indices[indexIndices++] = numberVertices - 1u;
			shape->indices[indexIndices++] = numberParallels * (numberSlices + 1u) + i;
		}
	}

	shape->CalculateTangent();

	return shape;
}

glShape* glShape::CreateCylinder(const GLuint numberSlices, const GLfloat radius, const GLfloat height) {
	return CreateCone(numberSlices, radius, radius, height);
}

glShape* glShape::CreateTorus(const GLuint numberSlices, const GLuint numberRings, const GLfloat innerRadius, const GLfloat outterRadius) {
	GLuint numberVertices = (numberRings + 1u) * (numberSlices + 1u);
	GLuint numberIndices = numberRings * numberSlices * 6u;

	assert(innerRadius > 0u);
	assert(outterRadius > 0u);
	assert(numberSlices >= 3u);
	assert(numberIndices < MAX_INDICES);
	assert(numberVertices < MAX_VERTICES);

	GLfloat ringAngleStep = M_2PI / numberRings;
	GLfloat sliceAngleStep = M_2PI / numberSlices;

	glShape* shape = new glShape(numberVertices, numberIndices);

	for (GLuint i = 0u; i < numberRings + 1u; i++) {
		for (GLuint j = 0u; j < numberSlices + 1u; j++) {
			GLuint index = (i * (numberSlices + 1u) + j);
			GLfloat dist = outterRadius + innerRadius * cosf(j * sliceAngleStep);

			shape->vertices[index] = Vector3f(cosf(i * ringAngleStep) * dist, -sinf(i * ringAngleStep) * dist, innerRadius * sinf(j * sliceAngleStep));
			shape->normals[index] = Vector3f(cosf(i * ringAngleStep) * cosf(j * sliceAngleStep), sinf(i * ringAngleStep) * cosf(j * sliceAngleStep), sinf(j * sliceAngleStep));
			shape->texCoords[index] = Vector2f(j / (GLfloat)numberSlices, 1.0f - i / (GLfloat)numberRings);
		}
	}

	GLuint indexIndices = 0u;
	for (GLuint i = 0u; i < numberRings; i++) {
		for (GLuint j = 0u; j < numberSlices; j++) {
			shape->indices[indexIndices++] = i * (numberSlices + 1u) + j;
			shape->indices[indexIndices++] = (i + 1u) * (numberSlices + 1u) + (j + 1u);
			shape->indices[indexIndices++] = (i + 1u) * (numberSlices + 1u) + j;

			shape->indices[indexIndices++] = i * (numberSlices + 1u) + j;
			shape->indices[indexIndices++] = i * (numberSlices + 1u) + (j + 1u);
			shape->indices[indexIndices++] = (i + 1u) * (numberSlices + 1u) + (j + 1u);
		}
	}

	shape->CalculateTangent();

	return shape;
}

void glShape::CalculateTangent() {
	Vector3f* bitangents = new Vector3f[vertexCount];

	for (GLuint i = 0u; i < indexCount; i += 3u) {
		GLuint idx0 = indices[i];
		GLuint idx1 = indices[i + 1u];
		GLuint idx2 = indices[i + 2u];

		Vector3f w = vertices[idx1] - vertices[idx0];
		Vector3f v = vertices[idx2] - vertices[idx0];

		Vector2f s = texCoords[idx1] - texCoords[idx0];
		Vector2f t = texCoords[idx2] - texCoords[idx0];
		GLfloat dirCorrection = 1.0f / (t.x * s.y - t.y * s.x);

		Vector3f tangent = (w * t.y - v * s.y) * dirCorrection;
		Vector3f bitangent = (v * s.x - w * t.x) * dirCorrection;

		tangents[idx0] += tangent;
		tangents[idx1] += tangent;
		tangents[idx2] += tangent;

		bitangents[idx0] += bitangent;
		bitangents[idx1] += bitangent;
		bitangents[idx2] += bitangent;
	}

	for (GLuint i = 0; i < vertexCount; i++) {
		Vector3f& bitangent = bitangents[i];
		Vector3f& tangent = tangents[i];
		Vector3f& normal = normals[i];

		tangent = tangent - normal * normal.dotProduct(tangent);

		if (normal.crossProduct(tangent).dotProduct(bitangent) < 0.0f)
			tangent = -tangent;

		tangent.normalize();
	}

	delete[] bitangents;
	bitangents = nullptr;
}

glShape::~glShape() {
	if (tangents) {
		delete[] tangents;
		tangents = nullptr;
	}

	if (vertices) {
		delete[] vertices;
		vertices = nullptr;
	}

	if (normals) {
		delete[] normals;
		normals = nullptr;
	}

	if (texCoords) {
		delete[] texCoords;
		texCoords = nullptr;
	}

	if (indices) {
		delete[] indices;
		indices = nullptr;
	}
}