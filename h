private void DrawBookmark(PdfPageBase contentPage, PdfPageBase tocPage, string title, PointF point)
{
    contentPage.Canvas.DrawString(title, new PdfFont(PdfFontFamily.Helvetica, 10f), new PdfSolidBrush(Color.Black), point);

    PdfDestination dest = new PdfDestination(contentPage);
    dest.Location = new PointF(0, contentPage.Size.Height - point.Y);

    PdfOutline outline = new PdfOutline(title, dest); // Create PdfOutline with title and destination

    // If the root outline (tocPage.Outlines.Count == 0)
    if (tocPage.Outlines.Count == 0)
    {
        tocPage.Outlines.Add(outline);
    }
    else // Add as child to the last outline
    {
        tocPage.Outlines[tocPage.Outlines.Count - 1].SubPoints.Add(outline);
    }
}







private void DrawBookmark(PdfPageBase contentPage, PdfPageBase tocPage, string title, PointF point)
{
    contentPage.Canvas.DrawString(title, new PdfFont(PdfFontFamily.Helvetica, 10f), new PdfSolidBrush(Color.Black), point);

    PdfDestination dest = new PdfDestination(contentPage);
    dest.Location = new PointF(0, contentPage.Size.Height - point.Y);

    PdfBookmark bookmark = new PdfBookmark(title); // Use the constructor with title parameter
    bookmark.Destination = dest;

    // If the root bookmark (tocPage.Bookmarks.Count == 0)
    if (tocPage.Bookmarks.Count == 0)
    {
        tocPage.Bookmarks.Add(bookmark);
    }
    else // Add as child to the last bookmark
    {
        tocPage.Bookmarks[tocPage.Bookmarks.Count - 1].SubBookmarks.Add(bookmark);
    }
}





using Spire.Pdf;
using System;
using System.Drawing;
using System.Web.UI;

namespace SpirePdfExample
{
    public partial class Default : Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void btnGeneratePDF_Click(object sender, EventArgs e)
        {
            PdfDocument document = new PdfDocument();
            PdfPageBase tocPage = document.Pages.Add();
            PdfPageBase contentPage = document.Pages.Add();

            DrawTOCHeader(tocPage);
            DrawContents(contentPage, tocPage);

            string filePath = Server.MapPath("~/TableOfContents.pdf");
            document.SaveToFile(filePath);
            document.Close();

            Response.Clear();
            Response.ContentType = "application/pdf";
            Response.AppendHeader("Content-Disposition", "attachment; filename=TableOfContents.pdf");
            Response.TransmitFile(filePath);
            Response.End();
        }

        private void DrawTOCHeader(PdfPageBase page)
        {
            PdfStringFormat format = new PdfStringFormat();
            format.Alignment = PdfTextAlignment.Center;
            format.LineAlignment = PdfVerticalAlignment.Middle;

            page.Canvas.DrawString("Table Of Contents", new PdfFont(PdfFontFamily.Helvetica, 10f), new PdfSolidBrush(Color.Black), new PointF(0, 0), format);
        }

        private void DrawContents(PdfPageBase contentPage, PdfPageBase tocPage)
        {
            float yPos = 30;

            for (int i = 1; i <= 2; i++)
            {
                DrawChapter(contentPage, tocPage, i, ref yPos);
            }
        }

        private void DrawChapter(PdfPageBase contentPage, PdfPageBase tocPage, int chapterNumber, ref float yPos)
        {
            DrawBookmark(contentPage, tocPage, "Chapter " + chapterNumber, new PointF(10, yPos));
            yPos += 20;

            for (int sectionNumber = 1; sectionNumber <= 2; sectionNumber++)
            {
                DrawSection(contentPage, tocPage, chapterNumber, sectionNumber, ref yPos);
            }
        }

        private void DrawSection(PdfPageBase contentPage, PdfPageBase tocPage, int chapterNumber, int sectionNumber, ref float yPos)
        {
            DrawBookmark(contentPage, tocPage, "Section " + chapterNumber + "." + sectionNumber, new PointF(30, yPos));
            yPos += 20;

            for (int paragraphNumber = 1; paragraphNumber <= 3; paragraphNumber++)
            {
                DrawParagraph(contentPage, tocPage, chapterNumber, sectionNumber, paragraphNumber, ref yPos);
            }
        }

        private void DrawParagraph(PdfPageBase contentPage, PdfPageBase tocPage, int chapterNumber, int sectionNumber, int paragraphNumber, ref float yPos)
        {
            DrawBookmark(contentPage, tocPage, "Paragraph " + chapterNumber + "." + sectionNumber + "." + paragraphNumber, new PointF(50, yPos));
            yPos += 20;
        }

        private void DrawBookmark(PdfPageBase contentPage, PdfPageBase tocPage, string title, PointF point)
        {
            contentPage.Canvas.DrawString(title, new PdfFont(PdfFontFamily.Helvetica, 10f), new PdfSolidBrush(Color.Black), point);

            PdfDestination dest = new PdfDestination(contentPage);
            dest.Location = new PointF(0, contentPage.Size.Height - point.Y);

            PdfBookmark bookmark = new PdfBookmark();
            bookmark.Title = title;
            tocPage.Bookmarks.Add(bookmark);
        }
    }
}







private void DrawBookmark(PdfPageBase contentPage, PdfPageBase tocPage, string title, PointF point)
{
    contentPage.Canvas.DrawString(title, new PdfFont(PdfFontFamily.Helvetica, 10f), new PdfSolidBrush(Color.Black), point);

    PdfDestination dest = new PdfDestination(contentPage);
    dest.Location = new PointF(0, contentPage.Size.Height - point.Y);

    PdfBookmark bookmark = new PdfBookmark();
    bookmark.Title = title;
    bookmark.Destination = dest;

    // If the root bookmark (tocPage.Bookmarks.Count == 0)
    if (tocPage.Bookmarks.Count == 0)
    {
        tocPage.Bookmarks.Add(bookmark);
    }
    else // Add as child to the last bookmark
    {
        tocPage.Bookmarks[tocPage.Bookmarks.Count - 1].SubBookmarks.Add(bookmark);
    }
}






using Spire.Pdf;
using Spire.Pdf.Annotations;
using Spire.Pdf.General;
using Spire.Pdf.Graphics;
using System;
using System.Drawing;

namespace SpirePdfExample
{
    public partial class Default : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void btnGeneratePDF_Click(object sender, EventArgs e)
        {
            PdfDocument document = new PdfDocument();
            PdfPageBase tocPage = document.Pages.Add();
            PdfPageBase contentPage = document.Pages.Add();

            DrawTOCHeader(tocPage);
            DrawContents(contentPage, tocPage);

            string filePath = Server.MapPath("~/TableOfContents.pdf");
            document.SaveToFile(filePath);
            document.Close();

            Response.Clear();
            Response.ContentType = "application/pdf";
            Response.AppendHeader("Content-Disposition", "attachment; filename=TableOfContents.pdf");
            Response.TransmitFile(filePath);
            Response.End();
        }

        private void DrawTOCHeader(PdfPageBase page)
        {
            PdfStringFormat format = new PdfStringFormat();
            format.Alignment = PdfTextAlignment.Center;
            format.LineAlignment = PdfVerticalAlignment.Middle;

            page.Canvas.DrawString("Table Of Contents", new PdfTrueTypeFont(new Font("Helvetica", 10f), true), PdfBrushes.Black, new RectangleF(0, 0, page.Canvas.ClientSize.Width, 20), format);
        }

        private void DrawContents(PdfPageBase contentPage, PdfPageBase tocPage)
        {
            float yPos = 30;

            for (int i = 1; i <= 2; i++)
            {
                DrawChapter(contentPage, tocPage, i, ref yPos);
            }
        }

        private void DrawChapter(PdfPageBase contentPage, PdfPageBase tocPage, int chapterNumber, ref float yPos)
        {
            DrawBookmark(document, tocPage, "Chapter " + chapterNumber, contentPage, yPos);
            yPos += 20;

            for (int sectionNumber = 1; sectionNumber <= 2; sectionNumber++)
            {
                DrawSection(contentPage, tocPage, chapterNumber, sectionNumber, ref yPos);
            }
        }

        private void DrawSection(PdfPageBase contentPage, PdfPageBase tocPage, int chapterNumber, int sectionNumber, ref float yPos)
        {
            DrawBookmark(document, tocPage, "Section " + chapterNumber + "." + sectionNumber, contentPage, yPos);
            yPos += 20;

            for (int paragraphNumber = 1; paragraphNumber <= 3; paragraphNumber++)
            {
                DrawParagraph(contentPage, tocPage, chapterNumber, sectionNumber, paragraphNumber, ref yPos);
            }
        }

        private void DrawParagraph(PdfPageBase contentPage, PdfPageBase tocPage, int chapterNumber, int sectionNumber, int paragraphNumber, ref float yPos)
        {
            DrawBookmark(document, tocPage, "Paragraph " + chapterNumber + "." + sectionNumber + "." + paragraphNumber, contentPage, yPos);
            yPos += 20;
        }

        private void DrawBookmark(PdfDocument document, PdfPageBase tocPage, string title, PdfPageBase contentPage, float yPos)
        {
            contentPage.Canvas.DrawString(title, new PdfTrueTypeFont(new Font("Helvetica", 10f), true), PdfBrushes.Black, new PointF(0, yPos));

            PdfDestination dest = new PdfDestination(contentPage);
            dest.Location = new PointF(0, contentPage.Size.Height - yPos);

            PdfOutlineItem bookmark = new PdfOutlineItem(title);
            bookmark.Destination = dest;
            tocPage.Outlines.Add(bookmark);
        }
    }
}






using Spire.Pdf;
using Spire.Pdf.Annotations;
using Spire.Pdf.General;
using Spire.Pdf.Graphics;
using System;
using System.Drawing;

namespace SpirePdfExample
{
    public partial class Default : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void btnGeneratePDF_Click(object sender, EventArgs e)
        {
            PdfDocument document = new PdfDocument();
            PdfPageBase tocPage = document.Pages.Add();
            PdfPageBase contentPage = document.Pages.Add();

            DrawTOCHeader(tocPage);
            DrawContents(contentPage, tocPage);

            string filePath = Server.MapPath("~/TableOfContents.pdf");
            document.SaveToFile(filePath);
            document.Close();

            Response.Clear();
            Response.ContentType = "application/pdf";
            Response.AppendHeader("Content-Disposition", "attachment; filename=TableOfContents.pdf");
            Response.TransmitFile(filePath);
            Response.End();
        }

        private void DrawTOCHeader(PdfPageBase page)
        {
            PdfStringFormat format = new PdfStringFormat();
            format.Alignment = PdfTextAlignment.Center;
            format.LineAlignment = PdfVerticalAlignment.Middle;

            page.Canvas.DrawString("Table Of Contents", new PdfTrueTypeFont(new Font("Helvetica", 10f), true), PdfBrushes.Black, new RectangleF(0, 0, page.Canvas.ClientSize.Width, 20), format);
        }

        private void DrawContents(PdfPageBase contentPage, PdfPageBase tocPage)
        {
            float yPos = 30;

            for (int i = 1; i <= 2; i++)
            {
                DrawChapter(contentPage, tocPage, i, ref yPos);
            }
        }

        private void DrawChapter(PdfPageBase contentPage, PdfPageBase tocPage, int chapterNumber, ref float yPos)
        {
            DrawBookmark(contentPage, tocPage, "Chapter " + chapterNumber, new PointF(10, yPos));
            yPos += 20;

            for (int sectionNumber = 1; sectionNumber <= 2; sectionNumber++)
            {
                DrawSection(contentPage, tocPage, chapterNumber, sectionNumber, ref yPos);
            }
        }

        private void DrawSection(PdfPageBase contentPage, PdfPageBase tocPage, int chapterNumber, int sectionNumber, ref float yPos)
        {
            DrawBookmark(contentPage, tocPage, "Section " + chapterNumber + "." + sectionNumber, new PointF(30, yPos));
            yPos += 20;

            for (int paragraphNumber = 1; paragraphNumber <= 3; paragraphNumber++)
            {
                DrawParagraph(contentPage, tocPage, chapterNumber, sectionNumber, paragraphNumber, ref yPos);
            }
        }

        private void DrawParagraph(PdfPageBase contentPage, PdfPageBase tocPage, int chapterNumber, int sectionNumber, int paragraphNumber, ref float yPos)
        {
            DrawBookmark(contentPage, tocPage, "Paragraph " + chapterNumber + "." + sectionNumber + "." + paragraphNumber, new PointF(50, yPos));
            yPos += 20;
        }

        private void DrawBookmark(PdfPageBase contentPage, PdfPageBase tocPage, string title, PointF point)
        {
            contentPage.Canvas.DrawString(title, new PdfTrueTypeFont(new Font("Helvetica", 10f), true), PdfBrushes.Black, point);

            PdfDestination dest = new PdfDestination(contentPage);
            dest.Location = new PointF(0, contentPage.Size.Height - point.Y);

            PdfBookmark bookmark = new PdfBookmark();
            bookmark.Title = title;
            bookmark.Destination = dest;
            tocPage.Bookmarks.Add(bookmark);
        }
    }
}







using Spire.Pdf;
using Spire.Pdf.Annotations;
using Spire.Pdf.General;
using Spire.Pdf.Graphics;
using System;
using System.Drawing;

namespace SpirePdfExample
{
    public partial class Default : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void btnGeneratePDF_Click(object sender, EventArgs e)
        {
            PdfDocument document = new PdfDocument();
            PdfPageBase tocPage = document.Pages.Add();
            PdfPageBase contentPage = document.Pages.Add();

            DrawTOCHeader(tocPage);
            DrawContents(contentPage, tocPage);

            string filePath = Server.MapPath("~/TableOfContents.pdf");
            document.SaveToFile(filePath);
            document.Close();

            Response.Clear();
            Response.ContentType = "application/pdf";
            Response.AppendHeader("Content-Disposition", "attachment; filename=TableOfContents.pdf");
            Response.TransmitFile(filePath);
            Response.End();
        }

        private void DrawTOCHeader(PdfPageBase page)
        {
            PdfStringFormat format = new PdfStringFormat();
            format.Alignment = PdfTextAlignment.Center; // Corrected the enumeration name here
            format.LineAlignment = PdfVerticalAlignment.Middle;

            page.Canvas.DrawString("Table Of Contents", new PdfTrueTypeFont(new Font("Helvetica", 10f), true), PdfBrushes.Black, new RectangleF(0, 0, page.Canvas.ClientSize.Width, 20), format);
        }

        private void DrawContents(PdfPageBase contentPage, PdfPageBase tocPage)
        {
            float yPos = 30;

            for (int i = 1; i <= 2; i++)
            {
                DrawChapter(contentPage, tocPage, i, ref yPos);
            }
        }

        private void DrawChapter(PdfPageBase contentPage, PdfPageBase tocPage, int chapterNumber, ref float yPos)
        {
            DrawBookmark(contentPage, tocPage, "Chapter " + chapterNumber, new PointF(10, yPos));
            yPos += 20;

            for (int sectionNumber = 1; sectionNumber <= 2; sectionNumber++)
            {
                DrawSection(contentPage, tocPage, chapterNumber, sectionNumber, ref yPos);
            }
        }

        private void DrawSection(PdfPageBase contentPage, PdfPageBase tocPage, int chapterNumber, int sectionNumber, ref float yPos)
        {
            DrawBookmark(contentPage, tocPage, "Section " + chapterNumber + "." + sectionNumber, new PointF(30, yPos));
            yPos += 20;

            for (int paragraphNumber = 1; paragraphNumber <= 3; paragraphNumber++)
            {
                DrawParagraph(contentPage, tocPage, chapterNumber, sectionNumber, paragraphNumber, ref yPos);
            }
        }

        private void DrawParagraph(PdfPageBase contentPage, PdfPageBase tocPage, int chapterNumber, int sectionNumber, int paragraphNumber, ref float yPos)
        {
            DrawBookmark(contentPage, tocPage, "Paragraph " + chapterNumber + "." + sectionNumber + "." + paragraphNumber, new PointF(50, yPos));
            yPos += 20;
        }

        private void DrawBookmark(PdfPageBase contentPage, PdfPageBase tocPage, string title, PointF point)
        {
            contentPage.Canvas.DrawString(title, new PdfTrueTypeFont(new Font("Helvetica", 10f), true), PdfBrushes.Black, point);

            PdfDestination dest = new PdfDestination(contentPage);
            dest.Location = new PointF(0, contentPage.Size.Height - point.Y);

            PdfBookmark bookmark = new PdfBookmark();
            bookmark.Title = title;
            bookmark.Destination = dest;

            tocPage.Bookmarks.Add(bookmark);
        }
    }
}









using Spire.Pdf;
using Spire.Pdf.Annotations;
using Spire.Pdf.General;
using Spire.Pdf.Graphics;
using System;
using System.Drawing;

namespace SpirePdfExample
{
    public partial class Default : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void btnGeneratePDF_Click(object sender, EventArgs e)
        {
            PdfDocument document = new PdfDocument();
            PdfPageBase tocPage = document.Pages.Add();
            PdfPageBase contentPage = document.Pages.Add();

            DrawTOCHeader(tocPage);
            DrawContents(contentPage, tocPage);

            string filePath = Server.MapPath("~/TableOfContents.pdf");
            document.SaveToFile(filePath);
            document.Close();

            Response.Clear();
            Response.ContentType = "application/pdf";
            Response.AppendHeader("Content-Disposition", "attachment; filename=TableOfContents.pdf");
            Response.TransmitFile(filePath);
            Response.End();
        }

        private void DrawTOCHeader(PdfPageBase page)
        {
            PdfStringFormat format = new PdfStringFormat();
            format.Alignment = PdfTextAlignment.Center;
            format.LineAlignment = PdfVerticalAlignment.Middle;

            page.Canvas.DrawString("Table Of Contents", new PdfTrueTypeFont(new Font("Helvetica", 10f), true), PdfBrushes.Black, new RectangleF(0, 0, page.Canvas.ClientSize.Width, 20), format);
        }

        private void DrawContents(PdfPageBase contentPage, PdfPageBase tocPage)
        {
            float yPos = 30;

            for (int i = 1; i <= 2; i++)
            {
                DrawChapter(contentPage, tocPage, i, ref yPos);
            }
        }

        private void DrawChapter(PdfPageBase contentPage, PdfPageBase tocPage, int chapterNumber, ref float yPos)
        {
            DrawBookmark(contentPage, tocPage, "Chapter " + chapterNumber, new PointF(10, yPos));
            yPos += 20;

            for (int sectionNumber = 1; sectionNumber <= 2; sectionNumber++)
            {
                DrawSection(contentPage, tocPage, chapterNumber, sectionNumber, ref yPos);
            }
        }

        private void DrawSection(PdfPageBase contentPage, PdfPageBase tocPage, int chapterNumber, int sectionNumber, ref float yPos)
        {
            DrawBookmark(contentPage, tocPage, "Section " + chapterNumber + "." + sectionNumber, new PointF(30, yPos));
            yPos += 20;

            for (int paragraphNumber = 1; paragraphNumber <= 3; paragraphNumber++)
            {
                DrawParagraph(contentPage, tocPage, chapterNumber, sectionNumber, paragraphNumber, ref yPos);
            }
        }

        private void DrawParagraph(PdfPageBase contentPage, PdfPageBase tocPage, int chapterNumber, int sectionNumber, int paragraphNumber, ref float yPos)
        {
            DrawBookmark(contentPage, tocPage, "Paragraph " + chapterNumber + "." + sectionNumber + "." + paragraphNumber, new PointF(50, yPos));
            yPos += 20;
        }

        private void DrawBookmark(PdfPageBase contentPage, PdfPageBase tocPage, string title, PointF point)
        {
            contentPage.Canvas.DrawString(title, new PdfTrueTypeFont(new Font("Helvetica", 10f), true), PdfBrushes.Black, point);

            PdfDestination dest = new PdfDestination(contentPage);
            dest.Location = new PointF(0, contentPage.Size.Height - point.Y);

            PdfBookmark bookmark = new PdfBookmark(title, dest);
            tocPage.Bookmarks.Add(bookmark);
        }
    }
}








<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Default.aspx.cs" Inherits="SpirePdfExample.Default" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>Generate PDF</title>
</head>
<body>
    <form id="form1" runat="server">
        <div>
            <asp:Button ID="btnGeneratePDF" runat="server" Text="Generate PDF" OnClick="btnGeneratePDF_Click" />
        </div>
    </form>
</body>
</html>








using Spire.Pdf;
using Spire.Pdf.Annotations;
using Spire.Pdf.General;
using Spire.Pdf.Graphics;
using System;
using System.Drawing;

namespace SpirePdfExample
{
    public partial class Default : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void btnGeneratePDF_Click(object sender, EventArgs e)
        {
            PdfDocument document = new PdfDocument();
            PdfPageBase tocPage = document.Pages.Add();
            PdfPageBase contentPage = document.Pages.Add();

            DrawTOCHeader(tocPage);
            DrawContents(contentPage, tocPage);

            string filePath = Server.MapPath("~/TableOfContents.pdf");
            document.SaveToFile(filePath);
            document.Close();

            Response.Clear();
            Response.ContentType = "application/pdf";
            Response.AppendHeader("Content-Disposition", "attachment; filename=TableOfContents.pdf");
            Response.TransmitFile(filePath);
            Response.End();
        }

        private void DrawTOCHeader(PdfPageBase page)
        {
            PdfStringFormat format = new PdfStringFormat();
            format.Alignment = PdfStringAlignment.Center;
            format.LineAlignment = PdfVerticalAlignment.Middle;

            page.Canvas.DrawString("Table Of Contents", new PdfTrueTypeFont(new Font("Helvetica", 10f), true), PdfBrushes.Black, new RectangleF(0, 0, page.Canvas.ClientSize.Width, 20), format);
        }

        private void DrawContents(PdfPageBase contentPage, PdfPageBase tocPage)
        {
            float yPos = 30;

            for (int i = 1; i <= 2; i++)
            {
                DrawChapter(contentPage, tocPage, i, ref yPos);
            }
        }

        private void DrawChapter(PdfPageBase contentPage, PdfPageBase tocPage, int chapterNumber, ref float yPos)
        {
            DrawBookmark(contentPage, tocPage, "Chapter " + chapterNumber, new PointF(10, yPos));
            yPos += 20;

            for (int sectionNumber = 1; sectionNumber <= 2; sectionNumber++)
            {
                DrawSection(contentPage, tocPage, chapterNumber, sectionNumber, ref yPos);
            }
        }

        private void DrawSection(PdfPageBase contentPage, PdfPageBase tocPage, int chapterNumber, int sectionNumber, ref float yPos)
        {
            DrawBookmark(contentPage, tocPage, "Section " + chapterNumber + "." + sectionNumber, new PointF(30, yPos));
            yPos += 20;

            for (int paragraphNumber = 1; paragraphNumber <= 3; paragraphNumber++)
            {
                DrawParagraph(contentPage, tocPage, chapterNumber, sectionNumber, paragraphNumber, ref yPos);
            }
        }

        private void DrawParagraph(PdfPageBase contentPage, PdfPageBase tocPage, int chapterNumber, int sectionNumber, int paragraphNumber, ref float yPos)
        {
            DrawBookmark(contentPage, tocPage, "Paragraph " + chapterNumber + "." + sectionNumber + "." + paragraphNumber, new PointF(50, yPos));
            yPos += 20;
        }

        private void DrawBookmark(PdfPageBase contentPage, PdfPageBase tocPage, string title, PointF point)
        {
            contentPage.Canvas.DrawString(title, new PdfTrueTypeFont(new Font("Helvetica", 10f), true), PdfBrushes.Black, point);

            PdfDestination dest = new PdfDestination(contentPage);
            dest.Location = new PointF(0, contentPage.Size.Height - point.Y);

            PdfBookmark bookmark = new PdfBookmark(title, dest);
            tocPage.Bookmarks.Add(bookmark);
        }
    }
}









using Syncfusion.Pdf;
using Syncfusion.Pdf.Graphics;
using Syncfusion.Pdf.Interactive;
using System.Drawing


PdfDocument document = null;
PdfFont font = null;
PdfBrush brush = null;
float yPos;
private void button1_Click(object sender, EventArgs e)
{
    //Initialize a new instance for PdfDocuemnt
    document = new PdfDocument();
    //Set font for TOC and bookmark contents
    font = new PdfStandardFont(PdfFontFamily.Helvetica, 10f);
    //Set brush for TOC and bookmark contents
    brush = new PdfSolidBrush(Color.Black);
    //Add page for TOC
    PdfSection SectionTOC = document.Sections.Add();
    PdfPage pageTOC = SectionTOC.Pages.Add();
    PdfStringFormat format = new PdfStringFormat(PdfTextAlignment.Center, PdfVerticalAlignment.Middle);
    pageTOC.Graphics.DrawString("Table Of Contents", font, brush, new RectangleF(PointF.Empty, new SizeF(pageTOC.Graphics.ClientSize.Width, 20)), format);
    //Draw contents, bookmarks, and table of contents
    PdfSection SectionContent = document.Sections.Add();
    yPos = 30;
    for (int i = 1; i <= 2; i++)
    {
        PdfPage pageContent = SectionContent.Pages.Add();
        //Add bookmark in PDF document
        PdfBookmark bookmark = AddBookmark(pageContent, pageTOC, "Chapter " + i, new PointF(10, 30));
        //Add sections to bookmark
        PdfBookmark section1 = AddSection(bookmark, pageContent, pageTOC, "Section " + i + ".1", new PointF(30, 50), false);
        //Add subsections to section
        PdfBookmark subsection1 = AddSection(section1, pageContent, pageTOC, "Paragraph " + i + ".1.1", new PointF(50, 70), true);
        PdfBookmark subsection2 = AddSection(section1, pageContent, pageTOC, "Paragraph " + i + ".1.2", new PointF(50, 170), true);
        PdfBookmark subsection3 = AddSection(section1, pageContent, pageTOC, "Paragraph " + i + ".1.3", new PointF(50, 270), true);
        PdfBookmark section2 = AddSection(bookmark, pageContent, pageTOC, "Section " + i + ".2", new PointF(30, 420), false);
        PdfBookmark subsection4 = AddSection(section2, pageContent, pageTOC, "Paragraph " + i + ".2.1", new PointF(50, 440), true);
        PdfBookmark subsection5 = AddSection(section2, pageContent, pageTOC, "Paragraph " + i + ".2.2", new PointF(50, 570), true);
        PdfBookmark subsection6 = AddSection(section2, pageContent, pageTOC, "Paragraph " + i + ".2.3", new PointF(50, 680), true);
    }
    document.Save("TableOfContents.pdf");
    document.Close(true);
}
public PdfBookmark AddBookmark(PdfPage page, PdfPage toc, string title, PointF point)
{
    PdfGraphics graphics = page.Graphics;
    //Add bookmark in PDF document
    PdfBookmark bookmarks = document.Bookmarks.Add(title);
    //Draw the content in the PDF page
    graphics.DrawString(title, font, brush, new PointF(point.X, point.Y));
    //Add table of contents
    AddTableOfcontents(page, toc, title, point);
    //Adding bookmark with named destination
    PdfNamedDestination namedDestination = new PdfNamedDestination(title);
    namedDestination.Destination = new PdfDestination(page, new PointF(point.X, point.Y));
    namedDestination.Destination.Mode = PdfDestinationMode.FitToPage;
    document.NamedDestinationCollection.Add(namedDestination);
    bookmarks.NamedDestination = namedDestination;
    return bookmarks;
}
public PdfBookmark AddSection(PdfBookmark bookmark, PdfPage page, PdfPage toc, string title, PointF point, bool isSubSection)
{
    PdfGraphics graphics = page.Graphics;
    //Add bookmark in PDF document
    PdfBookmark bookmarks = bookmark.Add(title);
    //Draw the content in the PDF page
    graphics.DrawString(title, font, brush, new PointF(point.X, point.Y));
    //Add table of contents
    AddTableOfcontents(page, toc, title, point);
    //Adding bookmark with named destination
    PdfNamedDestination namedDestination = new PdfNamedDestination(title);
    namedDestination.Destination = new PdfDestination(page, new PointF(point.X, point.Y));
    if (isSubSection == true)
        namedDestination.Destination.Zoom = 2f;
    else
        namedDestination.Destination.Zoom = 1f;
    document.NamedDestinationCollection.Add(namedDestination);
    bookmarks.NamedDestination = namedDestination;
    return bookmarks;
}
public void AddTableOfcontents(PdfPage page, PdfPage toc, string title, PointF point)
{
    //Draw title in TOC
    PdfTextElement element = new PdfTextElement(title, font, PdfBrushes.Blue);
    //Set layout format for pagination of TOC
    PdfLayoutFormat format = new PdfLayoutFormat();
    format.Break = PdfLayoutBreakType.FitPage;
    format.Layout = PdfLayoutType.Paginate;
    PdfLayoutResult result = element.Draw(toc, new PointF(point.X, yPos), format);
    //Draw page number in TOC
    PdfTextElement pageNumber = new PdfTextElement(document.Pages.IndexOf(page).ToString(), font, brush);
    pageNumber.Draw(toc, new PointF(toc.Graphics.ClientSize.Width - 40, yPos));
    //Creates a new document link annotation
    RectangleF bounds = result.Bounds;
    bounds.Width = toc.Graphics.ClientSize.Width - point.X;
    PdfDocumentLinkAnnotation documentLinkAnnotation = new PdfDocumentLinkAnnotation(bounds);
    documentLinkAnnotation.AnnotationFlags = PdfAnnotationFlags.NoRotate;
    documentLinkAnnotation.Text = title;
    documentLinkAnnotation.Color = Color.Transparent;
    //Sets the destination
    documentLinkAnnotation.Destination = new PdfDestination(page);
    documentLinkAnnotation.Destination.Location = point;
    //Adds this annotation to a new page
    toc.Annotations.Add(documentLinkAnnotation);
    if (toc != result.Page)
    {
        yPos = result.Bounds.Height + 5;
    }
    else
    {
        yPos += result.Bounds.Height + 5;
    }
    toc = result.Page;
}






















using Spire.Pdf;
using Spire.Pdf.Actions;
using Spire.Pdf.Annotations;
using Spire.Pdf.General;
using Spire.Pdf.Graphics;
using System;
using System.Drawing;

namespace TableOfContents
{
    internal class Program
    {
        static void Main(string[] args)
        {
            //Initialize an instance of the PdfDocument class
            PdfDocument doc = new PdfDocument();
            //Load a PDF document
            doc.LoadFromFile("Sample.PDF");

            //Get the page count of the document
            int pageCount = doc.Pages.Count;

            //Insert a new page into the pdf document as the first page
            PdfPageBase tocPage = doc.Pages.Insert(0);

            //Draw TOC title on the new page
            string title = "Table of Contents";
            PdfTrueTypeFont titleFont = new PdfTrueTypeFont(new Font("Arial", 20, FontStyle.Bold));
            PdfStringFormat centerAlignment = new PdfStringFormat(PdfTextAlignment.Center, PdfVerticalAlignment.Middle);
            PointF location = new PointF(tocPage.Canvas.ClientSize.Width / 2, titleFont.MeasureString(title).Height + 10);
            tocPage.Canvas.DrawString(title, titleFont, PdfBrushes.CornflowerBlue, location, centerAlignment);

            //Draw TOC content on the new page
            PdfTrueTypeFont titlesFont = new PdfTrueTypeFont(new Font("Arial", 14));
            String[] titles = new String[pageCount];
            for (int i = 0; i < titles.Length; i++)
            {
                titles[i] = string.Format("This is page {0}", i + 1);
            }
            float y = titleFont.MeasureString(title).Height + 10;
            float x = 0;

            //Draw page numbers of the target pages on the new page
            for (int i = 1; i <= pageCount; i++)
            {
                string text = titles[i - 1];
                SizeF titleSize = titlesFont.MeasureString(text);

                PdfPageBase navigatedPage = doc.Pages[i];

                string pageNumText = (i + 1).ToString();
                SizeF pageNumTextSize = titlesFont.MeasureString(pageNumText);
                tocPage.Canvas.DrawString(text, titlesFont, PdfBrushes.CadetBlue, 0, y);
                float dotLocation = titleSize.Width + 2 + x;
                float pageNumlocation = tocPage.Canvas.ClientSize.Width - pageNumTextSize.Width;
                for (float j = dotLocation; j < pageNumlocation; j++)
                {
                    if (dotLocation >= pageNumlocation)
                    {
                        break;
                    }
                    tocPage.Canvas.DrawString(".", titlesFont, PdfBrushes.Gray, dotLocation, y);
                    dotLocation += 3;
                }
                tocPage.Canvas.DrawString(pageNumText, titlesFont, PdfBrushes.CadetBlue, pageNumlocation, y);

                //Add actions that will take you to the target pages when clicked on to the new page
                location = new PointF(0, y);
                RectangleF titleBounds = new RectangleF(location, new SizeF(tocPage.Canvas.ClientSize.Width, titleSize.Height));
                PdfDestination Dest = new PdfDestination(navigatedPage, new PointF(-doc.PageSettings.Margins.Top, -doc.PageSettings.Margins.Left));
                PdfActionAnnotation action = new PdfActionAnnotation(titleBounds, new PdfGoToAction(Dest));
                action.Border = new PdfAnnotationBorder(0);
                (tocPage as PdfNewPage).Annotations.Add(action);
                y += titleSize.Height + 10;
            }

            //Save the result pdf document
            doc.SaveToFile("AddTableOfContents.pdf");
            doc.Close();
        }
    }
}

















private bool CreateTOC(string SubjectNo, string foldername, string Subjectinitial)
	{
		FileInfo fInfo = null;
		string PathforLocal = string.Empty;
		int av = 1;
		int ileft = 0;
		int itop = 0;
		int ipages = 0;
		int splitchar = 0;
		ileft = 0;
		itop = 0;
		splitchar = 0;
		ipages = 1;
		object lst1 = null;
		string strtitle = null;
		string strpage = null;
		string siteid = null;
		int i1 = 0;
		strtitle = "";
		strpage = "";
		siteid = "";
		iTextSharp.text.Chunk c = new iTextSharp.text.Chunk();
		iTextSharp.text.Chunk cPagenumber = new iTextSharp.text.Chunk();
		iTextSharp.text.Chunk cPagenumberTest = new iTextSharp.text.Chunk();
		iTextSharp.text.Chunk cDottedline = null;
		List<string> strsub = new List<string>();
		iTextSharp.text.pdf.PdfAction action = null;
		string strcommand = "";

		//Dim strdot As String = ".............................................................................................................................................................."
		try
		{
			if (!Directory.Exists(Server.MapPath(ConfigurationManager.AppSettings["uploadfilepath"].Trim() + "\\" + this.HProjectId.Value.ToString() + "\\" + foldername + "\\FinalReport")))
			{
				Directory.CreateDirectory(Server.MapPath(ConfigurationManager.AppSettings["uploadfilepath"].Trim() + "\\" + this.HProjectId.Value.ToString() + "\\" + foldername + "\\FinalReport"));
			}

			byte[] downloadbytes = System.IO.File.ReadAllBytes(Server.MapPath(ConfigurationManager.AppSettings["uploadfilepath"].Trim()) + "\\" + this.HProjectId.Value.ToString() + "\\" + foldername + "\\Report\\02.pdf");
			iTextSharp.text.pdf.PdfReader reader = new iTextSharp.text.pdf.PdfReader(downloadbytes);
			//List<Dictionary<string, object>> lst = iTextSharp.text.pdf.SimpleBookmark.GetBookmark(reader);
            var lst = iTextSharp.text.pdf.SimpleBookmark.GetBookmark(reader);
            iTextSharp.text.pdf.PdfStamper stamper = new iTextSharp.text.pdf.PdfStamper(reader, new FileStream(Server.MapPath(ConfigurationManager.AppSettings["uploadfilepath"].Trim()) + "\\" + this.HProjectId.Value.ToString() + "\\" + foldername + "\\FinalReport\\" + SubjectNo + ".pdf", FileMode.Create), '4');
			stamper.Writer.SetPdfVersion(iTextSharp.text.pdf.PdfWriter.PDF_VERSION_1_4); //'Added By ketan
			stamper.InsertPage(1, reader.GetPageSize(1));

			string pagewidth = (reader.GetPageSize(1).Width).ToString();
			itop = Convert.ToInt32(reader.GetPageSize(1).Height - 27);
			iTextSharp.text.pdf.PdfContentByte canvas = stamper.GetOverContent(1);
			string fontpath = Server.MapPath("Reports") + "\\times.ttf";
			iTextSharp.text.pdf.BaseFont customfont = iTextSharp.text.pdf.BaseFont.CreateFont(fontpath, iTextSharp.text.pdf.BaseFont.CP1252, iTextSharp.text.pdf.BaseFont.EMBEDDED);
			iTextSharp.text.Font font1 = new iTextSharp.text.Font(customfont, 12, 1, iTextSharp.text.BaseColor.BLACK);
			iTextSharp.text.Font font2 = new iTextSharp.text.Font(customfont, 12, 0, iTextSharp.text.BaseColor.BLUE);
			iTextSharp.text.Font font3 = new iTextSharp.text.Font(customfont, 12, 1, iTextSharp.text.BaseColor.BLUE);
			iTextSharp.text.Font Whitefont = new iTextSharp.text.Font(customfont, 12, 1, iTextSharp.text.BaseColor.WHITE);
			if (!this.AddHeader(canvas, stamper, reader, itop, 1, SubjectNo, Subjectinitial))
			{
				return false;
			}

			itop -= 140;

			if (lst.Count > 0)
			{
				c = new iTextSharp.text.Chunk("TABLE OF CONTENTS");
				c.Font = font1;
				iTextSharp.text.pdf.ColumnText.ShowTextAligned(canvas, iTextSharp.text.Element.ALIGN_CENTER, new iTextSharp.text.Phrase(c), Convert.ToSingle(Convert.ToSingle(pagewidth) / 2), itop, 0);
				Dictionary<string, object> Hashtable1 = new Dictionary<string, object>();
				Hashtable1.Add("Title", "TABLE OF CONTENTS");
				Hashtable1.Add("Page", "1 XYZ 0 685 .00");
				Hashtable1.Add("Action", "GoTo");
				lst.Insert(0, Hashtable1);
			}

			int j2 = 0;
			int ipage = 1;
			int itopcount = itop;
			if (!this.PagesCount(lst, c, ref ileft, ref pagewidth, ref itopcount, ref ipage, ref reader, ref font2, ref font3))
			{
				throw new Exception();
			}
			else
			{
				j2 = ipage;
			}

			for (int i = 0; i < lst.Count; i++)
			{
				strsub.Clear();
				itop -= 20;
				if (itop < 72)
				{
					ipages += 1;
					stamper.InsertPage(ipages, reader.GetPageSize(1));
					canvas = stamper.GetOverContent(ipages);
					itop = Convert.ToInt32(reader.GetPageSize(1).Height - 27);
					if (!this.AddHeader(canvas, stamper, reader, itop, ipages, SubjectNo, Subjectinitial))
					{
						return false;
					}
					itop -= 160;
				}
				else
				{
					canvas = stamper.GetOverContent(ipages);
				}

				ileft = 72;
				dynamic lst2 = lst[i];
				i1 += 1;
				action = new iTextSharp.text.pdf.PdfAction();

				if (lst2.TryGetValue("Title", strtitle))
				{
					c = new iTextSharp.text.Chunk(strtitle);
					c.Font = font3;
					c.SetBackground(iTextSharp.text.BaseColor.WHITE);
					if (c.GetWidthPoint() + ileft > Convert.ToInt32(Convert.ToInt32(pagewidth) - 47))
					{
						if (ileft == 82)
						{
							splitchar = 66;
						}
						else if (ileft == 92)
						{
							splitchar = 65;
						}
						else if (ileft == 102)
						{
							splitchar = 64;
						}
						else if (ileft == 72)
						{
							splitchar = 67;
						}

						string strtemp = Convert.ToString(strtitle.Length / (double)splitchar);
						if (strtitle.Length <= splitchar)
						{
							strtemp = "0";
						}
//INSTANT C# NOTE: The ending condition of VB 'For' loops is tested only on entry to the loop. Instant C# has created a temporary variable in order to use the initial value of Convert.ToInt16(strtemp.Split(".")(0)) for every iteration:
						int tempVar = Convert.ToInt16(strtemp.Split('.')[0]);
						for (int i2 = 0; i2 <= tempVar; i2++)
						{
							if (i2 == 0)
							{
								if (Convert.ToInt16(strtemp.Split('.')[0]) == 0)
								{
									strsub.Add(strtitle.Substring(i2 * splitchar, strtitle.Length));
								}
								else
								{
									strsub.Add(strtitle.Substring(i2 * splitchar, splitchar));
								}
							}
							else
							{
								strsub.Add(strtitle.Substring(i2 * splitchar - 1, strtitle.Length - (i2 * splitchar - 1)));
							}
						}
					}
					else
					{
						strsub.Add(strtitle.Substring(0, strtitle.Length));
					}
				}

				//------------------For Text------------------------------
				action.Put(iTextSharp.text.pdf.PdfName.S, iTextSharp.text.pdf.PdfName.GOTO);
				if (lst2.TryGetValue("Page", strpage))
				{
					strpage = strpage.Replace("XYZ", "/XYZ");

					if (strsub[0].ToUpper() == "TABLE OF CONTENTS")
					{
						action.Put(iTextSharp.text.pdf.PdfName.D, new iTextSharp.text.pdf.PdfLiteral("[" + "0" + " " + strpage.Split(' ')[1] + " " + strpage.Split(' ')[2] + " " + strpage.Split(' ')[3] + " " + strpage.Split(' ')[4] + "]"));
					}
					else
					{
						action.Put(iTextSharp.text.pdf.PdfName.D, new iTextSharp.text.pdf.PdfLiteral("[" + Convert.ToInt32(Convert.ToInt32(strpage.Split(' ')[0]) + j2 - 1).ToString() + " " + strpage.Split(' ')[1] + " " + strpage.Split(' ')[2] + " " + strpage.Split(' ')[3] + " " + strpage.Split(' ')[4] + "]"));
					}
				}

				cDottedline = new iTextSharp.text.Chunk(new iTextSharp.text.pdf.draw.DottedLineSeparator());
				cDottedline.Font = font3;
				// cDottedline.SetAction(action)
				if (strsub.Count == 1)
				{
					//-------------------For Dotted line-------------------------
					iTextSharp.text.pdf.ColumnText.ShowTextAligned(canvas, iTextSharp.text.Element.ALIGN_LEFT, new iTextSharp.text.Phrase(cDottedline), ileft, itop, 0);
					//-----------------------------------------------------------
				}
				else
				{
					iTextSharp.text.pdf.ColumnText.ShowTextAligned(canvas, iTextSharp.text.Element.ALIGN_LEFT, new iTextSharp.text.Phrase(cDottedline), ileft, itop - ((strsub.Count - 1) * 20), 0);
				}
				for (int i3 = 0; i3 < strsub.Count; i3++)
				{
					if (i3 > 0)
					{
						itop -= 20;
					}
					c = new iTextSharp.text.Chunk(strsub[i3]);
					c.Font = font3;
					c.SetBackground(iTextSharp.text.BaseColor.WHITE);
					c.SetAction(action);
					iTextSharp.text.pdf.ColumnText.ShowTextAligned(canvas, iTextSharp.text.Element.ALIGN_LEFT, new iTextSharp.text.Phrase(c), ileft, itop, 0);
				}
				//-----------------------------------------------------------
				//------------------For page number--------------------------
				int intPageNo = 0;
				string strBlank_PageNo = null;
				if (lst2.TryGetValue("Page", strpage))
				{
					strpage = strpage.Replace("XYZ", "/XYZ");
					if (strsub[0].ToUpper() != "TABLE OF CONTENTS")
					{
						//cPagenumber = New iTextSharp.text.Chunk(Convert.ToString(Convert.ToInt32(strpage.Split(" ")(0)) + j2))
						intPageNo = Convert.ToInt32(strpage.Split(' ')[0]) + j2;
						strBlank_PageNo = "   " + intPageNo;
						cPagenumber = new iTextSharp.text.Chunk(strBlank_PageNo);
					}
					else
					{
						//cPagenumber = New iTextSharp.text.Chunk(Convert.ToString(Convert.ToInt32(strpage.Split(" ")(0))))
						intPageNo = Convert.ToInt32(strpage.Split(' ')[0]);
						strBlank_PageNo = "   " + intPageNo;
						cPagenumber = new iTextSharp.text.Chunk(strBlank_PageNo);
					}
					cPagenumber.Font = font3;
					cPagenumber.SetBackground(iTextSharp.text.BaseColor.WHITE);
				}
				//cPagenumber.SetAction(action)
				iTextSharp.text.pdf.ColumnText.ShowTextAligned(canvas, iTextSharp.text.Element.ALIGN_LEFT, new iTextSharp.text.Phrase(cPagenumber), Convert.ToSingle(Convert.ToInt32(pagewidth) - 49), itop, 0);

				int intRemoveExtraWidth = 37;
				intRemoveExtraWidth = intRemoveExtraWidth - (intPageNo.ToString().Length * 5);
				cPagenumberTest = new iTextSharp.text.Chunk(new iTextSharp.text.pdf.draw.DottedLineSeparator());
				cPagenumberTest.Font = Whitefont;
				cPagenumberTest.SetBackground(iTextSharp.text.BaseColor.WHITE);
				//cPagenumberTest.SetAction(action)
				iTextSharp.text.pdf.ColumnText.ShowTextAligned(canvas, iTextSharp.text.Element.ALIGN_LEFT, new iTextSharp.text.Phrase(cPagenumberTest), Convert.ToSingle(Convert.ToInt32(pagewidth) - intRemoveExtraWidth), itop, 0);
				//-----------------------------------------------------------
				if (strsub[0].ToUpper() != "TABLE OF CONTENTS")
				{
					lst[i]["Page"] = Convert.ToInt32(strpage.Split(' ')[0] + j2).ToString() + " " + strpage.Split(' ')[1].ToString() + " " + strpage.Split(' ')[2].ToString() + " " + strpage.Split(' ')[3].ToString() + " " + strpage.Split(' ')[4].ToString();
				}

				if (lst2.TryGetValue("Kids", lst1))
				{
					if (!Recursive1(SubjectNo, Subjectinitial, (IList<Dictionary<string, object>>)lst1, ref itop, ref ileft, ref ipages, stamper, reader, canvas, ref j2, ref font2, ref i1))
					{
						throw new Exception();
					}
				}
			}

			stamper.Outlines = lst;
			reader.ViewerPreferences = iTextSharp.text.pdf.PdfWriter.PageModeUseOutlines;

			stamper.Close();
			reader.Close();

			//'Enable if security needs.
			//Dim DocSecurity As Document = New Document(Server.MapPath(ConfigurationManager.AppSettings.Item("uploadfilepath").Trim()) + "\" + Me.HProjectId.Value.ToString() + "\" + foldername + "\Report\" + SubjectNo + "_1" + ".pdf")
			//DocSecurity.LicenseKey = "dfvo+uv66OPj6vrr6PTq+unr9Ovo9OPj4+P66g=="
			//DocSecurity.Security.CanEditContent = False
			//DocSecurity.Save(Server.MapPath(ConfigurationManager.AppSettings.Item("uploadfilepath").Trim()) + "\" + Me.HProjectId.Value.ToString() + "\" + foldername + "\FinalReport\" + SubjectNo + ".pdf")
			//DocSecurity.AutoCloseAppendedDocs = True
			//DocSecurity.Close()

			//====================Set pdf fast web view to yes================
			strcommand = Server.MapPath(ConfigurationManager.AppSettings["QPdfPath"].Trim()) + " --linearize " + "\"" + Server.MapPath(ConfigurationManager.AppSettings["uploadfilepath"].Trim()) + "\\" + this.HProjectId.Value.ToString() + "\\" + foldername + "\\FinalReport\\" + SubjectNo + ".pdf\" " + "\"" + Server.MapPath(ConfigurationManager.AppSettings["uploadfilepath"].Trim()) + "\\" + this.HProjectId.Value.ToString() + "\\" + foldername + "\\FinalReportLinear\\" + SubjectNo + ".pdf\" ";

			if (!Directory.Exists(Server.MapPath(ConfigurationManager.AppSettings["uploadfilepath"].Trim() + "\\" + this.HProjectId.Value.ToString() + "\\" + foldername + "\\FinalReportLinear")))
			{
				Directory.CreateDirectory(Server.MapPath(ConfigurationManager.AppSettings["uploadfilepath"].Trim() + "\\" + this.HProjectId.Value.ToString() + "\\" + foldername + "\\FinalReportLinear"));
			}

			System.Diagnostics.Process.Start("CMD", "/C" + strcommand);
			System.Diagnostics.Process proc = System.Diagnostics.Process.Start("CMD", "/C" + strcommand);
			proc.WaitForExit();
			proc.Close();
			proc.Dispose();
			//===========================================================

			return true;
		}
		catch (Exception ex)
		{
			this.ShowErrorMessage(ex.Message, "....CreateTOC", ex);
			return false;
		}
	}















public bool FindBlankPage(ref string DocRemove, byte[] bytes)
	{
		try
		{
			iTextSharp.text.pdf.PdfReader oreader = new iTextSharp.text.pdf.PdfReader(bytes);
			using (MemoryStream stream = new MemoryStream())
			{
				iTextSharp.text.pdf.PdfReader reader = new iTextSharp.text.pdf.PdfReader(bytes);
				bytes = null;
				for (int i = 1; i <= reader.NumberOfPages; i++)
				{
					object sOut = "";
					iTextSharp.text.pdf.parser.LocationTextExtractionStrategy its = new iTextSharp.text.pdf.parser.LocationTextExtractionStrategy();
					sOut = iTextSharp.text.pdf.parser.PdfTextExtractor.GetTextFromPage(oreader, i, its);
					if (Convert.ToString(sOut) == "")
					{
						DocRemove += (i - 1).ToString() + ",";
					}
				}
				stream.Dispose();
			}
			return true;
		}
		catch (Exception ex)
		{
			this.ShowErrorMessage(ex.Message, "Error While Get Blank Page! ", ex);
			return false;
		}
		finally
		{
		}
	}



















public bool GetBlankpage(ref Document d1, Document d2)
	{
		byte[] bytes = null;
		string DocRemove = string.Empty;
		string[] DocRemove_arry = null;
		try
		{
			bytes = d2.Save();
			iTextSharp.text.pdf.PdfReader oreader = new iTextSharp.text.pdf.PdfReader(bytes);

			using (MemoryStream stream = new MemoryStream())
			{
				iTextSharp.text.pdf.PdfReader reader = new iTextSharp.text.pdf.PdfReader(bytes);
				bytes = null;
				using (iTextSharp.text.pdf.PdfStamper stamper = new iTextSharp.text.pdf.PdfStamper(reader, stream))
				{
					for (int i = 1; i <= reader.NumberOfPages; i++)
					{
						object sOut = "";
						iTextSharp.text.pdf.parser.LocationTextExtractionStrategy its = new iTextSharp.text.pdf.parser.LocationTextExtractionStrategy();
						sOut = iTextSharp.text.pdf.parser.PdfTextExtractor.GetTextFromPage(oreader, i, its);
						if (Convert.ToString(sOut) == "")
						{
							DocRemove += (i - 1).ToString() + ",";
						}
					}
				}
				stream.Dispose();
			}

			if (DocRemove.Length > 0)
			{
				DocRemove_arry = DocRemove.Substring(0, DocRemove.Length - 1).Split(',');
				for (int i = DocRemove_arry.Length - 1; i >= 0; i--)
				{
					d1.Pages.Remove(Convert.ToInt32(DocRemove_arry[i]));
				}
			}
			return true;

		}
		catch (Exception ex)
		{
			this.ShowErrorMessage(ex.Message, "Error While Get Blank Page! ", ex);
			return false;
		}
		finally
		{
		}
	}












create table of contents in html to pdf with links using asp.net spire.pdf






using Spire.Pdf;
using Spire.Pdf.Graphics;
using Spire.Pdf.Tables;
using System;
using System.Collections.Generic;
using System.Drawing;

namespace PdfTableOfContents
{
    public partial class WebForm1 : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void btnGeneratePdf_Click(object sender, EventArgs e)
        {
            // Create a new PDF document
            PdfDocument doc = new PdfDocument();

            // Add a new page to the document
            PdfPageBase page = doc.Pages.Add();

            // Create a font for the title
            PdfFont fontTitle = new PdfFont(PdfFontFamily.Helvetica, 16f, PdfFontStyle.Bold);

            // Create a font for the table of contents entries
            PdfFont fontTOC = new PdfFont(PdfFontFamily.Helvetica, 12f);

            // Title
            string title = "Sample Document";
            PointF titlePosition = new PointF(50, 50);
            page.Canvas.DrawString(title, fontTitle, PdfBrushes.Black, titlePosition);

            // Generate some sample content with headings
            List<string> headings = new List<string>
            {
                "Introduction",
                "Section 1",
                "Section 2",
                "Conclusion"
            };

            // Store the page numbers of headings
            Dictionary<string, int> tocEntries = new Dictionary<string, int>();

            // Draw the headings and store their page numbers
            float yOffset = 100;
            foreach (string heading in headings)
            {
                yOffset += 20; // Adjust the vertical position for the next heading
                page.Canvas.DrawString(heading, fontTOC, PdfBrushes.Black, new PointF(50, yOffset));
                tocEntries.Add(heading, doc.Pages.Count); // Store the page number of the heading
            }

            // Create a new page for the table of contents
            PdfPageBase tocPage = doc.Pages.Add();

            // Draw the title for the table of contents
            tocPage.Canvas.DrawString("Table of Contents", fontTitle, PdfBrushes.Black, new PointF(50, 50));

            // Draw the table of contents entries
            yOffset = 100;
            foreach (var entry in tocEntries)
            {
                yOffset += 20;
                tocPage.Canvas.DrawString(entry.Key + " - Page " + entry.Value, fontTOC, PdfBrushes.Black, new PointF(50, yOffset));
            }

            // Save the PDF document
            string filePath = Server.MapPath("~/TableOfContents.pdf");
            doc.SaveToFile(filePath);
            doc.Close();

            // Offer the PDF file for download
            Response.ContentType = "application/pdf";
            Response.AppendHeader("Content-Disposition", "attachment; filename=TableOfContents.pdf");
            Response.TransmitFile(filePath);
            Response.End();
        }
    }
}









using Spire.Pdf;
using Spire.Pdf.Graphics;
using Spire.Pdf.Tables;
using System;
using System.Collections.Generic;
using System.Drawing;

namespace PdfTableOfContents
{
    public partial class WebForm1 : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void btnGeneratePdf_Click(object sender, EventArgs e)
        {
            // Create a new PDF document
            PdfDocument doc = new PdfDocument();

            // Add a new page to the document
            PdfPageBase page = doc.Pages.Add();

            // Create a font for the title
            PdfFont fontTitle = new PdfFont(PdfFontFamily.Helvetica, 16f, PdfFontStyle.Bold);

            // Create a font for the table of contents entries
            PdfFont fontTOC = new PdfFont(PdfFontFamily.Helvetica, 12f);

            // Title
            string title = "Sample Document";
            PointF titlePosition = new PointF(50, 50);
            page.Canvas.DrawString(title, fontTitle, PdfBrushes.Black, titlePosition);

            // Generate some sample content with headings
            List<string> headings = new List<string>
            {
                "Introduction",
                "Section 1",
                "Section 2",
                "Conclusion"
            };

            // Store the page numbers of headings
            Dictionary<string, int> tocEntries = new Dictionary<string, int>();

            // Draw the headings and store their page numbers
            float yOffset = 100;
            foreach (string heading in headings)
            {
                yOffset += 20; // Adjust the vertical position for the next heading
                page.Canvas.DrawString(heading, fontTOC, PdfBrushes.Black, new PointF(50, yOffset));
                tocEntries.Add(heading, doc.Pages.Count); // Store the page number of the heading
            }

            // Create a new page for the table of contents
            PdfPageBase tocPage = doc.Pages.Add();

            // Draw the title for the table of contents
            tocPage.Canvas.DrawString("Table of Contents", fontTitle, PdfBrushes.Black, new PointF(50, 50));

            // Draw the table of contents entries
            yOffset = 100;
            foreach (var entry in tocEntries)
            {
                yOffset += 20;
                tocPage.Canvas.DrawString(entry.Key + " - Page " + entry.Value, fontTOC, PdfBrushes.Black, new PointF(50, yOffset));
            }

            // Save the PDF document
            doc.Save(Response, "TableOfContents.pdf", ContentDisposition.Attachment, HttpReadType.Open);
            doc.Close();
            Response.End();
        }
    }
}







using Spire.Pdf;
using Spire.Pdf.Graphics;
using Spire.Pdf.Tables;
using System;
using System.Collections.Generic;
using System.Drawing;

public partial class GeneratePdfWithToc : System.Web.UI.Page
{
    protected void btnGeneratePdf_Click(object sender, EventArgs e)
    {
        // Create a new PDF document
        PdfDocument doc = new PdfDocument();

        // Add a page
        PdfPageBase page = doc.Pages.Add();

        // Create a PdfTable for the table of contents
        PdfTable tocTable = new PdfTable();
        tocTable.Style.CellPadding = 2;
        tocTable.Style.DefaultStyle.BackgroundBrush = PdfBrushes.LightGray;
        tocTable.Style.DefaultStyle.Font = new PdfTrueTypeFont(new Font("Arial", 10f), true);
        tocTable.Style.HeaderSource = PdfHeaderSource.Rows;
        tocTable.Style.HeaderRowCount = 1;

        // Define table headers
        tocTable.Headers.Add(1);
        tocTable.Headers[0].Cells[0].Value = "Table of Contents";

        // Add table columns
        tocTable.Columns.Add(200);

        // Define table content
        List<string> tocEntries = new List<string>();
        tocEntries.Add("Chapter 1: Introduction");
        tocEntries.Add("Chapter 2: Getting Started");
        tocEntries.Add("Chapter 3: Advanced Techniques");

        // Add TOC entries to the table
        foreach (string entry in tocEntries)
        {
            PdfRow row = tocTable.Rows.Add();
            row.Cells[0].Value = entry;
        }

        // Draw the TOC table on the page
        tocTable.Draw(page, new PointF(50, 50));

        // Add content after the TOC
        PdfStringFormat format = new PdfStringFormat();
        format.ParagraphIndent = 10;
        PdfFont font = new PdfTrueTypeFont(new Font("Arial", 12f), true);
        page.Canvas.DrawString("Chapter 1: Introduction", font, PdfBrushes.Black, new PointF(50, 200), format);
        page.Canvas.DrawString("This is the content of Chapter 1.", font, PdfBrushes.Black, new PointF(70, 230), format);

        // Save the PDF document
        string filePath = Server.MapPath("~/GeneratedFiles/DocumentWithToc.pdf");
        doc.SaveToFile(filePath);
        doc.Close();

        // Provide the generated PDF file for download
        Response.ContentType = "application/pdf";
        Response.AppendHeader("Content-Disposition", "attachment; filename=DocumentWithToc.pdf");
        Response.TransmitFile(filePath);
        Response.End();
    }
}












<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="GeneratePdfWithToc.aspx.cs" Inherits="GeneratePdfWithToc" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>Generate PDF with Table of Contents</title>
</head>
<body>
    <form id="form1" runat="server">
        <div>
            <asp:Button ID="btnGeneratePdf" runat="server" Text="Generate PDF with TOC" OnClick="btnGeneratePdf_Click" />
        </div>
    </form>
</body>
</html>











using Spire.Pdf;
using Spire.Pdf.HtmlConverter;
using System;
using System.Drawing;
using System.IO;
using System.Threading;

namespace ConvertHtmlStringToPdfWithoutPlugin
{
    public partial class HtmlToPdf : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void btnConvert_Click(object sender, EventArgs e)
        {
            if (fileUploadHtml.HasFile)
            {
                string fileName = Path.GetFileName(fileUploadHtml.PostedFile.FileName);
                string filePath = Server.MapPath("~/UploadedFiles/") + fileName;
                string pdfFileName = Path.ChangeExtension(fileName, ".pdf");
                string pdfFilePath = Server.MapPath("~/ConvertedFiles/") + pdfFileName;

                // Save uploaded HTML file
                fileUploadHtml.SaveAs(filePath);

                // Create a PdfDocument object
                PdfDocument doc = new PdfDocument();

                // Create a PdfPageSettings object
                PdfPageSettings setting = new PdfPageSettings();

                // Save page size and margins through the object
                setting.Size = new SizeF(1000, 1000);
                setting.Margins = new Spire.Pdf.Graphics.PdfMargins(20);

                // Create a PdfHtmlLayoutFormat object
                PdfHtmlLayoutFormat htmlLayoutFormat = new PdfHtmlLayoutFormat();

                // Set IsWaiting property to true
                htmlLayoutFormat.IsWaiting = true;

                // Read HTML string from uploaded file
                string htmlString = File.ReadAllText(filePath);

                // Load HTML from HTML string using LoadFromHTML method
                Thread thread = new Thread(() =>
                {
                    doc.LoadFromHTML(htmlString, true, setting, htmlLayoutFormat);
                });
                thread.SetApartmentState(ApartmentState.STA);
                thread.Start();
                thread.Join();

                // Save as a PDF file with the same name as uploaded HTML file
                doc.SaveToFile(pdfFilePath);
                doc.Close();
            }
        }
    }
}







using Spire.Pdf;
using Spire.Pdf.HtmlConverter;
using System;
using System.Drawing;
using System.IO;
using System.Threading;

namespace ConvertHtmlStringToPdfWithoutPlugin
{
    public partial class HtmlToPdf : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void btnConvert_Click(object sender, EventArgs e)
        {
            //Create a PdfDocument object
            PdfDocument doc = new PdfDocument();

            //Create a PdfPageSettings object
            PdfPageSettings setting = new PdfPageSettings();

            //Save page size and margins through the object
            setting.Size = new SizeF(1000, 1000);
            setting.Margins = new Spire.Pdf.Graphics.PdfMargins(20);

            //Create a PdfHtmlLayoutFormat object
            PdfHtmlLayoutFormat htmlLayoutFormat = new PdfHtmlLayoutFormat();

            //Set IsWaiting property to true
            htmlLayoutFormat.IsWaiting = true;

            //Read html string from uploaded file
            if (fileUploadHtml.HasFile)
            {
                string fileName = Path.GetFileName(fileUploadHtml.PostedFile.FileName);
                string filePath = Server.MapPath("~/UploadedFiles/") + fileName;
                fileUploadHtml.SaveAs(filePath);

                //Load HTML from html string using LoadFromHTML method
                string htmlString = File.ReadAllText(filePath);

                //Load HTML from html string using LoadFromHTML method
                Thread thread = new Thread(() =>
                { doc.LoadFromHTML(htmlString, true, setting, htmlLayoutFormat); });
                thread.SetApartmentState(ApartmentState.STA);
                thread.Start();
                thread.Join();

                //Save to a PDF file
                doc.SaveToFile(Server.MapPath("~/ConvertedFiles/HtmlToPdf.pdf"));
            }
        }
    }
}










<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="HtmlToPdf.aspx.cs" Inherits="ConvertHtmlStringToPdfWithoutPlugin.HtmlToPdf" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>Convert HTML String to PDF</title>
</head>
<body>
    <form id="form1" runat="server">
        <div>
            <asp:FileUpload ID="fileUploadHtml" runat="server" />
            <asp:Button ID="btnConvert" runat="server" Text="Convert to PDF" OnClick="btnConvert_Click" />
        </div>
    </form>
</body>
</html>










using Spire.Pdf;
using Spire.Pdf.HtmlConverter;
using System.IO;
using System.Threading;
using System.Drawing;

namespace ConvertHtmlStringToPdfWithoutPlugin
{
    class Program
    {
        static void Main(string[] args)
        {
            //Create a PdfDocument object
            PdfDocument doc = new PdfDocument();

            //Create a PdfPageSettings object
            PdfPageSettings setting = new PdfPageSettings();

            //Save page size and margins through the object
            setting.Size = new SizeF(1000, 1000);
            setting.Margins = new Spire.Pdf.Graphics.PdfMargins(20);

            //Create a PdfHtmlLayoutFormat object
            PdfHtmlLayoutFormat htmlLayoutFormat = new PdfHtmlLayoutFormat();

            //Set IsWaiting property to true
            htmlLayoutFormat.IsWaiting = true;

            //Read html string from a .html file
            string htmlString = File.ReadAllText(@"C:\Users\Administrator\Desktop\Document\Html\Sample.html");

            //Load HTML from html string using LoadFromHTML method
            Thread thread = new Thread(() =>
            { doc.LoadFromHTML(htmlString, true, setting, htmlLayoutFormat); });
            thread.SetApartmentState(ApartmentState.STA);
            thread.Start();
            thread.Join();

            //Save to a PDF file
            doc.SaveToFile("HtmlStringToPdf.pdf");
        }
    }
}








using System;
using Spire.Pdf;
using System.Threading;
using Spire.Pdf.HtmlConverter;
using System.Drawing;

namespace SPIREPDF_HTMLtoPDF
{
    public partial class UrlToPdf : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void btnConvert_Click(object sender, EventArgs e)
        {
            //Create a PdfDocument object
            PdfDocument doc = new PdfDocument();

            //Create a PdfPageSettings object
            PdfPageSettings setting = new PdfPageSettings();

            //Save page size and margins through the object
            setting.Size = new SizeF(1000, 1000);
            setting.Margins = new Spire.Pdf.Graphics.PdfMargins(20);

            //Create a PdfHtmlLayoutFormat object
            PdfHtmlLayoutFormat htmlLayoutFormat = new PdfHtmlLayoutFormat();

            //Set IsWaiting property to true
            htmlLayoutFormat.IsWaiting = true;

            //Specific the URL path to convert
            String url = "https://www.wikipedia.org/";

            //Load HTML from a URL path using LoadFromHTML method
            Thread thread = new Thread(() =>
            { doc.LoadFromHTML(url, true, true, false, setting, htmlLayoutFormat); });
            thread.SetApartmentState(ApartmentState.STA);
            thread.Start();
            thread.Join();

            //Save the document to a PDF file
            doc.SaveToFile(Server.MapPath("~/UrlToPdf.pdf"));
            doc.Close();
        }
    }
}












<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="UrlToPdf.aspx.cs" Inherits="SPIREPDF_HTMLtoPDF.UrlToPdf" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>Convert URL to PDF</title>
</head>
<body>
    <form id="form1" runat="server">
        <div>
            <asp:Button ID="btnConvert" runat="server" Text="Convert to PDF" OnClick="btnConvert_Click" />
        </div>
    </form>
</body>
</html>














using System;
using Spire.Pdf;
using System.Threading;
using Spire.Pdf.HtmlConverter;
using System.Drawing;

namespace SPIREPDF_HTMLtoPDF
{
    class Program
    {
        static void Main(string[] args)
        {
            //Create a PdfDocument object
            PdfDocument doc = new PdfDocument();

            //Create a PdfPageSettings object
            PdfPageSettings setting = new PdfPageSettings();

            //Save page size and margins through the object
            setting.Size = new SizeF(1000, 1000);
            setting.Margins = new Spire.Pdf.Graphics.PdfMargins(20);

            //Create a PdfHtmlLayoutFormat object
            PdfHtmlLayoutFormat htmlLayoutFormat = new PdfHtmlLayoutFormat();

            //Set IsWaiting property to true
            htmlLayoutFormat.IsWaiting = true;

            //Specific the URL path to convert
            String url = "https://www.wikipedia.org/";

            //Load HTML from a URL path using LoadFromHTML method
            Thread thread = new Thread(() =>
            { doc.LoadFromHTML(url, true, true, false, setting, htmlLayoutFormat); });
            thread.SetApartmentState(ApartmentState.STA);
            thread.Start();
            thread.Join();

            //Save the document to a PDF file
            doc.SaveToFile("UrlToPdf.pdf");
            doc.Close();
        }
    }
}














CREATE TABLE Customer (
    CustomerId INT PRIMARY KEY,
    CustomerName VARCHAR(255),
    City VARCHAR(255),
    Email VARCHAR(255),
    ContactNumber VARCHAR(20)
);









-- Inserting 10 entries into the Customer table
INSERT INTO Customer (CustomerId, CustomerName, City, Email, ContactNumber) VALUES
(1, 'Rahul Kumar', 'Delhi', 'rahul@example.com', '9876543210'),
(2, 'Priya Sharma', 'Mumbai', 'priya@example.com', '8765432109'),
(3, 'Amit Singh', 'Bangalore', 'amit@example.com', '7654321098'),
(4, 'Anjali Gupta', 'Kolkata', 'anjali@example.com', '6543210987'),
(5, 'Ravi Patel', 'Chennai', 'ravi@example.com', '5432109876'),
(6, 'Sunita Verma', 'Hyderabad', 'sunita@example.com', '4321098765'),
(7, 'Vikas Mishra', 'Pune', 'vikas@example.com', '3210987654'),
(8, 'Neha Reddy', 'Ahmedabad', 'neha@example.com', '2109876543'),
(9, 'Karan Gupta', 'Jaipur', 'karan@example.com', '1098765432'),
(10, 'Pooja Singh', 'Lucknow', 'pooja@example.com', '9876543210');










Server Error in '/' Application.
A potentially dangerous Request.Form value was detected from the client (hfGridHtml="
   <table cellspacing="...").
Description: ASP.NET has detected data in the request that is potentially dangerous because it might include HTML markup or script. The data might represent an attempt to compromise the security of your application, such as a cross-site scripting attack. If this type of input is appropriate in your application, you can include code in a web page to explicitly allow it. For more information, see http://go.microsoft.com/fwlink/?LinkID=212874.

Exception Details: System.Web.HttpRequestValidationException: A potentially dangerous Request.Form value was detected from the client (hfGridHtml="
   <table cellspacing="...").

Source Error:


[No relevant source lines]

Source File: C:\Windows\Microsoft.NET\Framework\v4.0.30319\Temporary ASP.NET Files\root\3abe6c24\2071dd7c\App_Web_h0uybqlo.2.cs    Line: 0







protected void ExportToPDF(object sender, EventArgs e)
{
    // Get the encoded content of hfGridHtml
    string encodedContent = Server.HtmlEncode(Request.Form[hfGridHtml.UniqueID]);

    // Create a StringReader to read the encoded content
    StringReader sr = new StringReader(encodedContent);

    // Create a new PDF document
    Document pdfDoc = new Document(PageSize.A4, 10f, 10f, 10f, 0f);

    // Set up the PdfWriter to write the PDF to the response stream
    PdfWriter writer = PdfWriter.GetInstance(pdfDoc, Response.OutputStream);

    // Open the PDF document
    pdfDoc.Open();

    // Parse the encoded HTML content and add it to the PDF document
    XMLWorkerHelper.GetInstance().ParseXHtml(writer, pdfDoc, sr);

    // Close the PDF document
    pdfDoc.Close();

    // Set the response content type and headers
    Response.ContentType = "application/pdf";
    Response.AddHeader("content-disposition", "attachment;filename=HTML.pdf");
    Response.Cache.SetCacheability(HttpCacheability.NoCache);

    // Write the PDF document to the response stream
    Response.Write(pdfDoc);

    // End the response
    Response.End();
}







An exception of type 'System.Web.HttpRequestValidationException' occurred in System.Web.dll but was not handled in user code

Additional information: A potentially dangerous Request.Form value was detected from the client (hfGridHtml="

    <table cellspacing="...").

 protected void ExportToPDF(object sender, EventArgs e)
        {
            StringReader sr = new StringReader(Request.Form[hfGridHtml.UniqueID]);
            Document pdfDoc = new Document(PageSize.A4, 10f, 10f, 10f, 0f);
            PdfWriter writer = PdfWriter.GetInstance(pdfDoc, Response.OutputStream);
            pdfDoc.Open();
            XMLWorkerHelper.GetInstance().ParseXHtml(writer, pdfDoc, sr);
            pdfDoc.Close();
            Response.ContentType = "application/pdf";
            Response.AddHeader("content-disposition", "attachment;filename=HTML.pdf");
            Response.Cache.SetCacheability(HttpCacheability.NoCache);
            Response.Write(pdfDoc);
            Response.End();
        }









<%@ Page Language="C#" AutoEventWireup="true" CodeFile="YourPageName.aspx.cs" Inherits="YourNamespace.YourPageName" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>HTML to PDF Conversion</title>
    <style>
        .form-container {
            max-width: 400px;
            margin: 0 auto;
            padding: 20px;
            border: 1px solid #ccc;
            border-radius: 5px;
            background-color: #f9f9f9;
        }
        .form-group {
            margin-bottom: 15px;
        }
        .form-group label {
            display: block;
            font-weight: bold;
        }
        .form-group input[type="text"], .form-group input[type="url"] {
            width: 100%;
            padding: 10px;
            border: 1px solid #ccc;
            border-radius: 4px;
            box-sizing: border-box;
        }
        .form-group input[type="file"] {
            margin-top: 5px;
        }
        .form-group button {
            padding: 10px 20px;
            background-color: #4CAF50;
            color: white;
            border: none;
            border-radius: 4px;
            cursor: pointer;
        }
        .form-group button:hover {
            background-color: #45a049;
        }
    </style>
</head>
<body>
    <form id="form1" runat="server">
        <div class="form-container">
            <div class="form-group">
                <label for="fileUpload">Upload HTML file:</label>
                <asp:FileUpload ID="fileUpload" runat="server" CssClass="form-control" />
            </div>
            <div class="form-group">
                <label for="firstUrlTextBox">or Enter URL:</label>
                <asp:TextBox ID="firstUrlTextBox" runat="server" CssClass="form-control" TextMode="Url"></asp:TextBox>
            </div>
            <div class="form-group">
                <asp:CheckBox ID="startNewPageCheckBox" runat="server" Text="Start New Page" />
            </div>
            <div class="form-group">
                <asp:Button ID="convertToPdfButton" runat="server" Text="Convert to PDF" OnClick="convertToPdfButton_Click" CssClass="btn btn-primary" />
            </div>
        </div>
    </form>
</body>
</html>





protected void convertToPdfButton_Click(object sender, EventArgs e)
{
    // Check if URL is provided
    if (!string.IsNullOrEmpty(firstUrlTextBox.Text))
    {
        // Create the PDF document
        Document pdfDocument = new Document();

        // Set license key received after purchase to use the converter in licensed mode
        // Leave it not set to use the converter in demo mode
        pdfDocument.LicenseKey = "fvDh8eDx4fHg4P/h8eLg/+Dj/+jo6Og=";

        // Create a PDF page
        PdfPage pdfPage = pdfDocument.AddPage();

        try
        {
            // Create the HTML to PDF element
            HtmlToPdfElement htmlToPdfElement = new HtmlToPdfElement(0, 0, firstUrlTextBox.Text);

            // Optionally set a delay before conversion to allow asynchronous scripts to finish
            htmlToPdfElement.ConversionDelay = 2;

            // Add the HTML to PDF document
            pdfPage.AddElement(htmlToPdfElement);

            // Save the PDF document to a memory buffer
            byte[] outPdfBuffer = pdfDocument.Save();

            // Generate a unique file name for the PDF
            string fileName = "ConvertedDocument.pdf";

            // Write the PDF document buffer to a file
            File.WriteAllBytes(Server.MapPath("~/PDFFiles/" + fileName), outPdfBuffer);
        }
        finally
        {
            // Close the PDF document
            pdfDocument.Close();
        }

        // Provide a download link for the generated PDF file
        Response.Redirect("~/DownloadPage.aspx");
    }
    else
    {
        // Handle error - URL is not provided
    }
}







An exception of type 'Winnovative.HtmlConvertException' occurred in wnvhtmltopdf.dll but was not handled in user code

Additional information: The URL to convert is null.











protected void mergePdfButton_Click(object sender, EventArgs e)
{
    // Create the merge result PDF document
    Document mergeResultPdfDocument = new Document();

    // Automatically close the merged documents when the document resulted after merge is closed
    mergeResultPdfDocument.AutoCloseAppendedDocs = true;

    // Set license key received after purchase to use the converter in licensed mode
    // Leave it not set to use the converter in demo mode
    mergeResultPdfDocument.LicenseKey = "fvDh8eDx4fHg4P/h8eLg/+Dj/+jo6Og=";

    try
    {
        // The documents to merge must remain opened until the PDF document resulted after merge is saved
        // The merged documents can be automatically closed when the document resulted after merge is closed
        // if the AutoCloseAppendedDocs property of the PDF document resulted after merge is set on true like
        // in this demo applcation

        // Load the first PDF document to merge
        string firstPdfFilePath = Server.MapPath("~/DemoAppFiles/Input/PDF_Files/Merge_Before_Conversion.pdf");
        Document firstPdfDocumentToMerge = new Document(firstPdfFilePath);
        // Merge the first PDF document
        mergeResultPdfDocument.AppendDocument(firstPdfDocumentToMerge);

        // Load the second PDF document to merge
        string secondPdfFilePath = Server.MapPath("~/DemoAppFiles/Input/PDF_Files/Merge_After_Conversion.pdf");
        Document secondPdfDocumentToMerge = new Document(secondPdfFilePath);
        // Merge the second PDF document
        mergeResultPdfDocument.AppendDocument(secondPdfDocumentToMerge);

        // Save the merge result PDF document in a memory buffer
        byte[] outPdfBuffer = mergeResultPdfDocument.Save();

        // Send the PDF as response to browser

        // Set response content type
        Response.AddHeader("Content-Type", "application/pdf");

        // Instruct the browser to open the PDF file as an attachment or inline
        Response.AddHeader("Content-Disposition", String.Format("attachment; filename=Merge_PDF.pdf; size={0}", outPdfBuffer.Length.ToString()));

        // Write the PDF document buffer to HTTP response
        Response.BinaryWrite(outPdfBuffer);

        // End the HTTP response and stop the current page processing
        Response.End();
    }
    finally
    {
        // Close the PDF document resulted after merge
        // When the AutoCloseAppendedDocs property is true the merged PDF documents will also be closed
        mergeResultPdfDocument.Close();
    }
}











<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="YourPageName.aspx.cs" Inherits="YourNamespace.YourPageName" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>HTML to PDF Conversion</title>
    <style>
        .form-container {
            max-width: 400px;
            margin: 0 auto;
            padding: 20px;
            border: 1px solid #ccc;
            border-radius: 5px;
            background-color: #f9f9f9;
        }
        .form-group {
            margin-bottom: 15px;
        }
        .form-group label {
            display: block;
            font-weight: bold;
        }
        .form-group input[type="file"] {
            margin-top: 5px;
        }
        .form-group input[type="submit"] {
            padding: 10px 20px;
            background-color: #4CAF50;
            color: white;
            border: none;
            border-radius: 4px;
            cursor: pointer;
        }
        .form-group input[type="submit"]:hover {
            background-color: #45a049;
        }
        .file-names {
            margin-top: 10px;
        }
        .file-names ul {
            list-style-type: none;
            padding: 0;
        }
        .file-names ul li {
            margin-bottom: 5px;
        }
    </style>
</head>
<body>
    <form id="form1" runat="server" enctype="multipart/form-data">
        <div class="form-container">
            <div class="form-group">
                <label for="fileUpload">Upload HTML files:</label>
                <asp:FileUpload ID="fileUpload" runat="server" CssClass="form-control" Multiple="true" />
            </div>
            <div class="form-group">
                <asp:Button ID="convertToPdfButton" runat="server" Text="Convert to PDF" OnClick="convertToPdfButton_Click" CssClass="btn btn-primary" />
            </div>
            <div class="file-names" runat="server" id="fileNamesDiv">
                <ul>
                    <!-- File names will be dynamically added here -->
                </ul>
            </div>
        </div>
    </form>
</body>
</html>






using System;
using System.IO;
using System.Web.UI;

namespace YourNamespace
{
    public partial class DownloadPage : Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                BindPdfFiles();
            }
        }

        private void BindPdfFiles()
        {
            string pdfDirectory = Server.MapPath("~/PDFFiles/");
            string[] pdfFiles = Directory.GetFiles(pdfDirectory, "*.pdf");

            foreach (string pdfFile in pdfFiles)
            {
                string fileName = Path.GetFileName(pdfFile);
                string pdfUrl = ResolveUrl("~/PDFFiles/" + fileName);

                pdfFilesRepeater.DataSource = pdfFiles;
                pdfFilesRepeater.DataBind();
            }
        }
    }
}





<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="DownloadPage.aspx.cs" Inherits="YourNamespace.DownloadPage" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>Download PDF Files</title>
</head>
<body>
    <form id="form1" runat="server">
        <div>
            <h2>Download PDF Files</h2>
            <asp:Repeater ID="pdfFilesRepeater" runat="server">
                <ItemTemplate>
                    <div>
                        <a href='<%# Eval("PdfUrl") %>' target="_blank"><%# Eval("FileName") %></a>
                    </div>
                </ItemTemplate>
            </asp:Repeater>
        </div>
    </form>
</body>
</html>



using System;
using System.Drawing;
using System.IO;
using System.Web;
using Winnovative.WnvHtmlConvert;

protected void convertToPdfButton_Click(object sender, EventArgs e)
{
    // Check if files were uploaded
    if (fileUpload.HasFiles)
    {
        // Create a PDF document for each uploaded file
        foreach (HttpPostedFile uploadedFile in fileUpload.PostedFiles)
        {
            // Ensure the file is of HTML format
            if (Path.GetExtension(uploadedFile.FileName).ToLower() == ".html")
            {
                // Create the PDF document
                Document pdfDocument = new Document();

                // Set license key received after purchase to use the converter in licensed mode
                // Leave it not set to use the converter in demo mode
                pdfDocument.LicenseKey = "fvDh8eDx4fHg4P/h8eLg/+Dj/+jo6Og=";

                // Create a PDF page
                PdfPage pdfPage = pdfDocument.AddPage();

                try
                {
                    // Create the HTML to PDF element
                    HtmlToPdfElement htmlToPdfElement = new HtmlToPdfElement(0, 0, uploadedFile.InputStream, "");

                    // Optionally set a delay before conversion to allow asynchronous scripts to finish
                    htmlToPdfElement.ConversionDelay = 2;

                    // Add the HTML to PDF document
                    pdfPage.AddElement(htmlToPdfElement);

                    // Generate a unique file name for the PDF
                    string fileName = Path.GetFileNameWithoutExtension(uploadedFile.FileName) + ".pdf";

                    // Write the PDF document to a file
                    pdfDocument.Save(Path.Combine(Server.MapPath("~/PDFFiles"), fileName));
                }
                finally
                {
                    // Close the PDF document
                    pdfDocument.Close();
                }
            }
        }

        // Provide a download link for the generated PDF files
        Response.Redirect("~/DownloadPage.aspx");
    }
    else
    {
        // No files uploaded, provide appropriate message
        // For example:
        // errorLabel.Text = "Please upload at least one HTML file.";
    }
}




<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="YourPageName.aspx.cs" Inherits="YourNamespace.YourPageName" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>HTML to PDF Conversion</title>
    <style>
        .form-container {
            max-width: 400px;
            margin: 0 auto;
            padding: 20px;
            border: 1px solid #ccc;
            border-radius: 5px;
            background-color: #f9f9f9;
        }
        .form-group {
            margin-bottom: 15px;
        }
        .form-group label {
            display: block;
            font-weight: bold;
        }
        .form-group input[type="text"], .form-group input[type="url"] {
            width: 100%;
            padding: 10px;
            border: 1px solid #ccc;
            border-radius: 4px;
            box-sizing: border-box;
        }
        .form-group input[type="file"] {
            margin-top: 5px;
        }
        .form-group button {
            padding: 10px 20px;
            background-color: #4CAF50;
            color: white;
            border: none;
            border-radius: 4px;
            cursor: pointer;
        }
        .form-group button:hover {
            background-color: #45a049;
        }
    </style>
</head>
<body>
    <form id="form1" runat="server">
        <div class="form-container">
            <div class="form-group">
                <asp:FileUpload ID="fileUpload" runat="server" CssClass="form-control" AllowMultiple="true" />
            </div>
            <div class="form-group">
                <asp:CheckBox ID="startNewPageCheckBox" runat="server" Text="Start New Page" />
            </div>
            <div class="form-group">
                <asp:Button ID="convertToPdfButton" runat="server" Text="Convert to PDF" OnClick="convertToPdfButton_Click" CssClass="btn btn-primary" />
            </div>
        </div>
    </form>
</body>
</html>
