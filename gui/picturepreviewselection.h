#ifndef COVEREDIT_H
#define COVEREDIT_H

#include "previousvaluehandling.h"

#include <tagparser/tag.h>

#include <QWidget>

#include <memory>

QT_BEGIN_NAMESPACE
class QEvent;
class QGraphicsScene;
class QGraphicsTextItem;
class QGraphicsPixmapItem;
class QGraphicsRectItem;
QT_END_NAMESPACE

namespace Media {
class Tag;
DECLARE_ENUM(KnownField, unsigned int)
class TagValue;
}

namespace QtGui {

DECLARE_ENUM(PreviousValueHandling, int)

namespace Ui {
class PicturePreviewSelection;
}

class PicturePreviewSelection : public QWidget
{
    Q_OBJECT

public:
    explicit PicturePreviewSelection(Media::Tag *tag = nullptr, Media::KnownField field = Media::KnownField::Invalid, QWidget *parent = nullptr);
    virtual ~PicturePreviewSelection();
    
    Media::Tag *tag() const;
    Media::KnownField field() const;

public slots:
    void setTagField(Media::Tag *tag, Media::KnownField field, PreviousValueHandling previousValueHandling = PreviousValueHandling::Clear);

    void apply();
    void clear();
    void addOfSelectedType();
    void removeSelected();
    void extractSelected();
    void displaySelected();

signals:
    void pictureChanged();

protected:
    void changeEvent(QEvent *event);
    void resizeEvent(QResizeEvent *event);

private slots:
    void typeSwitched(int index);
    void updateDescription(int newIndex);
    void updateDescription(int lastIndex, int newIndex);
    void updatePreview(int index);

private:
    void setup(PreviousValueHandling previousValueHandling = PreviousValueHandling::Clear);

    std::unique_ptr<Ui::PicturePreviewSelection> m_ui;
    QGraphicsScene *m_scene;
    QGraphicsTextItem *m_textItem;
    QPixmap m_pixmap;
    QGraphicsPixmapItem *m_pixmapItem;
    QGraphicsRectItem *m_rectItem;
    Media::Tag *m_tag;
    Media::KnownField m_field;
    QList<Media::TagValue> m_values;
    unsigned int m_currentTypeIndex;
};

/*!
 * \brief Returns the tied tag if one is assigned; returns nullptr otherwise.
 *
 * This might have been set initially using the constructor or using the setTagField() method.
 */
inline Media::Tag *PicturePreviewSelection::tag() const
{
    return m_tag;
}

/*!
 * \brief Returns the field. This is commonly KnownField::Cover.
 */
inline Media::KnownField PicturePreviewSelection::field() const
{
    return m_field;
}

/*!
 * \brief Sets the specified \a tag, \a field and \a previousValueHandling.
 *
 * If \a tag is nullptr the widget is disabled. The widget will be re-setup.
 */
inline void PicturePreviewSelection::setTagField(Media::Tag *tag, Media::KnownField field, PreviousValueHandling previousValueHandling)
{
    m_tag = tag;
    m_field = field;
    setup(previousValueHandling);
}

}

#endif // COVEREDIT_H