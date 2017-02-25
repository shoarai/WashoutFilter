class Position {
public:
  Position(const double &translationX, const double &translationY,
           const double &translationZ, const double &rotationX,
           const double &rotationY, const double &rotationZ)
      : m_x(translationX), m_y(translationY), m_z(translationZ),
        m_phi(rotationX), m_theta(rotationY), m_psi(rotationZ) {}
  ~Position(){};

  const double getTranslationX() const { return m_x; };
  const double getTranslationY() const { return m_y; };
  const double getTranslationZ() const { return m_z; };
  const double getRotationX() const { return m_phi; };
  const double getRotationY() const { return m_theta; };
  const double getRotationZ() const { return m_psi; };

private:
  double m_x, m_y, m_z, m_phi, m_theta, m_psi;
};
