#include "Panel.h"

#include "Camera.h"
#include "Debug.h"

Panel::Panel(Shader& shader, const std::vector<Texture>& textures, Camera& camera)
    :
    mShader(&shader),
    mTextures(textures),
    mCamera(&camera)
{
    float vertices[] = {
        // positions          // colors           // texture coords // normals
         1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,       0.0f, 0.0f, 1.0f,   // top right
         1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,       0.0f, 0.0f, 1.0f,   // bottom right
        -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,       0.0f, 0.0f, 1.0f,   // bottom left
        -1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,       0.0f, 0.0f, 1.0f    // top left 
    };
    glm::vec3 entityNormal = { 0.0f, 0.0f, 1.0f };

    mVertexData.insert(mVertexData.begin(), &vertices[0], &vertices[sizeof(vertices) / sizeof(float)]);

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    mIndexData.insert(mIndexData.begin(), &indices[0], &indices[sizeof(unsigned int) / sizeof(float)]);

    glm::vec3 fromEntityToCamera = glm::normalize(-camera.GetView().GetPosition() - mTransform.GetPosition());
    glm::vec3 axis = glm::normalize(glm::cross(fromEntityToCamera, entityNormal));
    float angle = acos(glm::dot(fromEntityToCamera, entityNormal));

    mTransform.SetOrientation(axis, -angle);

    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(3);
    layout.Push<float>(2);
    layout.Push<float>(3);
    mVAO.SetLayout(layout, false);
    mVAO.SetDrawingMode(GL_TRIANGLES);
    mVAO.SetUsage(GL_STATIC_DRAW);

    mVBO.FillBuffer(vertices, sizeof(vertices), GL_STATIC_DRAW);
    mIBO.FillBuffer(indices, sizeof(indices) / sizeof(unsigned int), GL_STATIC_DRAW);

    mVAO.AddBuffer(mVBO, mIBO);
}

bool Panel::IsDead() const
{
    return (mAliveTimer >= mLifeDuration) ? true : false;
}

void Panel::Update(float elapsedTime)
{
    mTimeElapsed += elapsedTime;
    mAliveTimer += elapsedTime;

    if (mAliveTimer >= mLifeDuration)
    {
        mAliveTimer = mLifeDuration + 1;
        return;
    }

    mTransform.SetScaleUniformly((mLifeDuration - mAliveTimer) / mLifeDuration);

    if (mTimeElapsed > mAnimationDuration)
        mTimeElapsed = 0.0f;

    mActiveTexture = floor(mTimeElapsed / (mAnimationDuration / mTextures.size())); // goes through all textures in half a second


    glm::vec3 fromEntityToCamera = glm::normalize(-mCamera->GetView().GetPosition() - mTransform.GetPosition());
    glm::vec3 axis = glm::normalize(glm::cross(fromEntityToCamera, {0.0f, 0.0f, 1.0f}));
    float angle = acos(glm::dot(fromEntityToCamera, {0.0f, 0.0f, 1.0f}));

    mTransform.SetOrientation(axis, -angle);
}

void Panel::Draw()
{
    mTextures[mActiveTexture].Bind();

    mShader->Bind();
    mShader->SetUniformMatrix4f("model", mTransform.GetMatrix());

    mVAO.Bind();
    mVBO.Bind(0, mVAO.GetLayout());
    mIBO.Bind();

    glDrawElements(mVAO.GetDrawingMode(), mIBO.GetIndicesCount(), GL_UNSIGNED_INT, 0);
}

void Panel::SetLifeDuration(const float& newLifeDuration)
{
    mLifeDuration = newLifeDuration;
}

Transform& Panel::GetTransform()
{
    return mTransform;
}
