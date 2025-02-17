#include "stdafx.h"
#include "Image_Widget.h"

Image_Widget::Image_Widget()
{
	m_sprite = std::make_shared<Sprite>();
	m_transform = std::make_shared<Transform>( m_sprite );
}

Image_Widget::~Image_Widget() {}

void Image_Widget::Initialize( ID3D11Device* device, ID3D11DeviceContext* context, ConstantBuffer<Matrices>& mat )
{
	m_sprite->Initialize( device, context, m_sTextFile, mat );
}

void Image_Widget::Update( const float dt )
{
	m_transform->Update();
}

void Image_Widget::Draw( ID3D11Device* device, ID3D11DeviceContext* context, XMMATRIX worldOrtho, TextRenderer* textRenderer )
{
	m_sprite->UpdateTex( device, m_sTextFile );
	m_sprite->UpdateBuffers( context );
	m_sprite->Draw( m_transform->GetWorldMatrix(), worldOrtho );

	// image text
	XMVECTOR textsize = textRenderer->GetSpriteFont( m_eFontSize )->MeasureString( m_sText.c_str() );
	XMFLOAT2 textpos =
	{
		m_transform->GetPosition().x + ( m_sprite->GetWidth() / 2.0f ) - ( XMVectorGetX( textsize ) * textRenderer->GetScale().x ) / 2.0f,
		m_transform->GetPosition().y + ( m_sprite->GetHeight() / 2.0f ) - ( XMVectorGetY( textsize ) * textRenderer->GetScale().y ) / 2.0f
	};
	textRenderer->RenderString( m_sText, textpos, m_vTextColor, m_eFontSize, true );
}

void Image_Widget::Resolve( const std::string& text, XMVECTORF32 textColour, const std::string& texture, FontSize size )
{
	m_sText = text;
	m_eFontSize = size;
	m_vTextColor = textColour;

	if ( m_sTextFile != texture )
		m_sTextFile = texture;
}