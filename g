using iText.Kernel.Pdf;
using iText.Kernel.Utils;

namespace PDFMerge
{
    public class PDFMerge
    {
        private static string[] INPUT_FILES = { "/uploads/first.pdf", "/uploads/second.pdf" };
        private static string OUTPUT_FOLDER = "/myfiles/";
        
        static void Main(string[] args)
        {
            MergePDFs(INPUT_FILES, OUTPUT_FOLDER + "merged.pdf");
        }

        public static void MergePDFs(string[] inputFiles, string outputFile)
        {
            using (PdfDocument resultDocument = new PdfDocument(new PdfWriter(outputFile)))
            {
                foreach (string inputFile in inputFiles)
                {
                    using (PdfDocument pdfDocument = new PdfDocument(new PdfReader(inputFile)))
                    {
                        PdfMerger merger = new PdfMerger(resultDocument);
                        merger.Merge(pdfDocument, 1, pdfDocument.GetNumberOfPages());
                    }
                }
            }
        }
    }
}


<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>PDF Merger</title>
<style>
    #drop_zone {
        border: 2px dashed #ccc;
        width: 100%;
        height: 200px;
        text-align: center;
        padding: 50px 0;
        cursor: pointer;
    }
    #file_input {
        display: none;
    }
</style>
</head>
<body>

<div id="drop_zone" ondrop="dropHandler(event)" ondragover="dragOverHandler(event)">
    <p>Drag & drop PDF files here</p>
    <p>or</p>
    <label for="file_input">Click here to select files</label>
    <input type="file" id="file_input" multiple onchange="handleFiles(this.files)">
</div>

<button id="merge_btn" onclick="mergePDFs()">Merge PDFs</button>

<script>
    function dragOverHandler(event) {
        event.preventDefault();
        event.dataTransfer.dropEffect = 'copy';
    }

    function dropHandler(event) {
        event.preventDefault();
        var files = event.dataTransfer.files;
        handleFiles(files);
    }

    function handleFiles(files) {
        for (var i = 0; i < files.length; i++) {
            if (files[i].type === 'application/pdf') {
                // Handle PDF file
                console.log('PDF file:', files[i].name);
            } else {
                alert('Please select only PDF files.');
            }
        }
    }

    function mergePDFs() {
        // Send selected PDF files to server for merging
        // Implement server-side logic to merge PDFs and return the merged PDF file
        alert('Merging PDFs...');
        // Example: Use AJAX to send file data to server
    }
</script>

</body>
</html>




<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Sample HTML with Bookmarks and TOC</title>
</head>
<body>
    <h1 id="section1">Section 1</h1>
    <p>This is the content of section 1.</p>

    <h2 id="subSection1">Subsection 1.1</h2>
    <p>This is the content of subsection 1.1.</p>

    <h2 id="subSection2">Subsection 1.2</h2>
    <p>This is the content of subsection 1.2.</p>

    <h1 id="section2">Section 2</h1>
    <p>This is the content of section 2.</p>

    <h2 id="subSection3">Subsection 2.1</h2>
    <p>This is the content of subsection 2.1.</p>

    <h2 id="subSection4">Subsection 2.2</h2>
    <p>This is the content of subsection 2.2.</p>
</body>
</html>

using iText.Kernel.Pdf;
using iText.Layout;
using iText.Layout.Element;
using iText.Layout.Properties;
using iText.Html2pdf;

namespace PdfWithBookmarkAndTOC
{
    public class PdfGenerator
    {
        public static void GeneratePdfWithBookmarkAndTOC(string htmlContent, string outputPath)
        {
            // Convert HTML to PDF
            PdfDocument pdfDocument = new PdfDocument(new PdfWriter(outputPath));
            ConverterProperties converterProperties = new ConverterProperties();
            HtmlConverter.ConvertToPdf(htmlContent, pdfDocument, converterProperties);

            // Access PDF document
            Document document = new Document(pdfDocument);

            // Add bookmarks and TOC
            AddBookmarksAndTOC(document);

            // Close the document
            document.Close();
        }

        private static void AddBookmarksAndTOC(Document document)
        {
            // Iterate through document and add bookmarks for headings
            foreach (IBlockElement element in document.GetRenderer().GetModelElement().GetChildren())
            {
                if (element is Paragraph paragraph && paragraph.GetFirstRenderer() is ParagraphRenderer renderer)
                {
                    if (renderer.GetPropertyAsBoolean(Property.FIRST_PARAGRAPH) && paragraph.HasOwnProperty(Property.TITLE))
                    {
                        string title = paragraph.GetProperty(Property.TITLE).ToString();
                        document.Add(new Bookmark(title).AddDestinationPageOnly());
                    }
                }
            }

            // Generate table of contents
            document.Add(new AreaBreak(AreaBreakType.NEXT_PAGE));
            document.Add(new Paragraph("Table of Contents").SetTextAlignment(TextAlignment.CENTER).SetBold().SetFontSize(16));
            foreach (IBlockElement element in document.GetRenderer().GetModelElement().GetChildren())
            {
                if (element is Paragraph paragraph && paragraph.GetFirstRenderer() is ParagraphRenderer renderer)
                {
                    if (renderer.GetPropertyAsBoolean(Property.FIRST_PARAGRAPH) && paragraph.HasOwnProperty(Property.TITLE))
                    {
                        string title = paragraph.GetProperty(Property.TITLE).ToString();
                        document.Add(new Paragraph().Add(title).SetAction(PdfAction.CreateGoTo(title)));
                    }
                }
            }
        }
    }
}


You tried signing in with a different authentication method than the one you used during signup. Please try again using your original authentication method.


<asp:Button ID="merge_btn" runat="server" Text="Merge PDFs" OnClick="merge_btn_Click" />
<asp:Label ID="lblMessage" runat="server" Text=""></asp:Label>





<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>PDF Merger</title>
<style>
    #drop_zone {
        border: 2px dashed #ccc;
        width: 100%;
        height: 200px;
        text-align: center;
        padding: 50px 0;
        cursor: pointer;
    }
    #file_input {
        display: none;
    }
</style>
</head>
<body>

<div id="drop_zone" ondrop="dropHandler(event)" ondragover="dragOverHandler(event)">
    <p>Drag & drop PDF files here</p>
    <p>or</p>
    <label for="file_input">Click here to select files</label>
    <input type="file" id="file_input" multiple onchange="handleFiles(this.files)">
</div>

<button id="merge_btn" onclick="mergePDFs()">Merge PDFs</button>

<div id="upload_info"></div>

<script>
    function dragOverHandler(event) {
        event.preventDefault();
        event.dataTransfer.dropEffect = 'copy';
    }

    function dropHandler(event) {
        event.preventDefault();
        var files = event.dataTransfer.files;
        handleFiles(files);
    }

    function handleFiles(files) {
        var info = document.getElementById('upload_info');
        info.innerHTML = ''; // Clear previous info
        for (var i = 0; i < files.length; i++) {
            if (files[i].type === 'application/pdf') {
                // Handle PDF file
                info.innerHTML += 'Uploaded PDF: ' + files[i].name + '<br>';
            } else {
                alert('Please select only PDF files.');
            }
        }
        info.innerHTML += 'Total PDFs uploaded: ' + files.length;
    }

    function mergePDFs() {
        // Send selected PDF files to server for merging
        // Implement server-side logic to merge PDFs and return the merged PDF file
        alert('Merging PDFs...');
        // Example: Use AJAX to send file data to server
    }
</script>

</body>
</html>




private void GeneratePdfWithBookmarkAndTOC(string mergedPdfPath, string outputPath)
{
    // Create a new document
    Document document = new Document();
    // Create a PdfWriter instance to write the document to a file
    PdfWriter writer = new PdfWriter(outputPath);
    // Create a PdfDocument instance
    PdfDocument pdfDoc = new PdfDocument(writer);
    // Set the document to the PdfDocument instance
    pdfDoc.AddNewPage();

    try
    {
        // Create a PdfReader instance to read the merged PDF
        PdfReader reader = new PdfReader(mergedPdfPath);
        // Create a PdfDocument instance for the merged PDF
        PdfDocument mergedPdfDoc = new PdfDocument(reader);

        // Initialize variables for bookmark and TOC generation
        int totalPages = mergedPdfDoc.GetNumberOfPages();
        PdfOutline root = pdfDoc.GetOutlines(false);

        // Create a PdfDocument instance for the TOC page
        PdfDocument tocPdfDoc = new PdfDocument(writer);

        // Create a PdfCanvas instance to draw content on the TOC page
        PdfCanvas canvas = new PdfCanvas(tocPdfDoc.AddNewPage());

        // Add the title for the TOC page
        new Canvas(canvas, pdfDoc, new iText.Kernel.Geom.Rectangle(36, 36, 523, 770))
            .Add(new Paragraph("Table of Contents")
            .SetTextAlignment(TextAlignment.CENTER)
            .SetFontSize(20));

        // Create a list to hold TOC entries
        List<TocEntry> tocEntries = new List<TocEntry>();

        // Iterate through pages of the merged PDF
        for (int i = 1; i <= totalPages; i++)
        {
            // Add a bookmark for each page
            PdfPage page = mergedPdfDoc.GetPage(i);
            PdfOutline outline = root.AddOutline("Page " + i);
            outline.AddDestination(PdfDestination.MakeDestination(new PdfPageDestination(page)));

            // Create TOC entry
            TocEntry tocEntry = new TocEntry();
            tocEntry.Title = "Page " + i;
            tocEntry.PageNumber = i;
            tocEntries.Add(tocEntry);

            // Add page number to TOC page
            Paragraph p = new Paragraph().Add("Page ").Add(i.ToString());
            p.SetFixedPosition(i, 36, 770, 100);
            new Canvas(canvas, pdfDoc, new iText.Kernel.Geom.Rectangle(36, 36, 523, 770)).Add(p);
        }

        // Add TOC entries to the TOC page
        foreach (var entry in tocEntries)
        {
            PdfOutline tocOutline = root.AddOutline(entry.Title);
            tocOutline.AddDestination(PdfDestination.MakeDestination(new PdfPageDestination(mergedPdfDoc.GetPage(entry.PageNumber))));
        }
    }
    catch (Exception ex)
    {
        // Handle any exceptions
        lblMessage.Text = "An error occurred while generating PDF with bookmarks and TOC: " + ex.Message;
    }
    finally
    {
        // Close the document
        pdfDoc.Close();
    }
}

// Class to hold TOC entries
public class TocEntry
{
    public string Title { get; set; }
    public int PageNumber { get; set; }
}




using System;
using System.IO;
using System.Web;
using iTextSharp.text;
using iTextSharp.text.pdf;

public partial class YourPageName : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {
    }

    protected void merge_btn_Click(object sender, EventArgs e)
    {
        // Check if any files were uploaded
        if (Request.Files.Count == 0)
        {
            // No files uploaded, display error message
            lblMessage.Text = "Please upload PDF files before merging.";
            return;
        }

        // Create a temporary directory to store uploaded files
        string tempDirectory = Server.MapPath("~/TempFiles/");
        Directory.CreateDirectory(tempDirectory);

        try
        {
            // Merge uploaded PDF files
            string mergedPdfPath = MergePdfFiles(tempDirectory);

            // Generate PDF with bookmarks and TOC
            GeneratePdfWithBookmarkAndTOC(mergedPdfPath, "output.pdf");

            // Display success message
            lblMessage.Text = "PDF files merged successfully and TOC generated.";
        }
        catch (Exception ex)
        {
            // Handle any exceptions and display error message
            lblMessage.Text = "An error occurred: " + ex.Message;
        }
        finally
        {
            // Clean up temporary directory (delete uploaded files)
            Directory.Delete(tempDirectory, true);
        }
    }

    private string MergePdfFiles(string tempDirectory)
    {
        string mergedPdfPath = Path.Combine(tempDirectory, "merged.pdf");
        using (FileStream mergedPdfStream = new FileStream(mergedPdfPath, FileMode.Create))
        {
            Document document = new Document();
            PdfCopy copy = new PdfCopy(document, mergedPdfStream);
            document.Open();

            foreach (string fileName in Request.Files)
            {
                HttpPostedFile uploadedFile = Request.Files[fileName];
                if (uploadedFile.ContentType == "application/pdf" && uploadedFile.ContentLength > 0)
                {
                    PdfReader reader = new PdfReader(uploadedFile.InputStream);
                    for (int i = 1; i <= reader.NumberOfPages; i++)
                    {
                        document.NewPage();
                        PdfImportedPage page = copy.GetImportedPage(reader, i);
                        copy.AddPage(page);
                    }
                    reader.Close();
                }
            }

            document.Close();
        }

        return mergedPdfPath;
    }

    private void GeneratePdfWithBookmarkAndTOC(string mergedPdfPath, string outputPath)
    {
        // Implement bookmark and TOC generation if needed
        // You can use iTextSharp for this purpose
        // For example:
        // PdfReader reader = new PdfReader(mergedPdfPath);
        // Document document = new Document();
        // PdfCopy copy = new PdfCopy(document, new FileStream(outputPath, FileMode.Create));
        // document.Open();
        // copy.AddDocument(reader);
        // document.Close();
        // reader.Close();
    }
}




private void GeneratePdfWithBookmarkAndTOC(string mergedPdfPath, string outputPath)
{
    try
    {
        // Create a PdfReader instance to read the merged PDF
        PdfReader reader = new PdfReader(mergedPdfPath);
        
        // Create a PdfStamper instance to write modifications to the PDF
        using (FileStream outputStream = new FileStream(outputPath, FileMode.Create))
        {
            using (PdfStamper stamper = new PdfStamper(reader, outputStream))
            {
                // Initialize variables for bookmark and TOC generation
                int totalPages = reader.NumberOfPages;
                PdfContentByte canvas;

                // Create a list to hold TOC entries
                List<TocEntry> tocEntries = new List<TocEntry>();

                // Iterate through pages of the merged PDF
                for (int i = 1; i <= totalPages; i++)
                {
                    // Add a bookmark for each page
                    PdfOutline root = stamper.Writer.RootOutline;
                    PdfDestination destination = new PdfDestination(PdfDestination.FITH);
                    PdfOutline outline = new PdfOutline(root, destination, "Page " + i);
                    stamper.Writer.SetOutlines(root);

                    // Create TOC entry
                    TocEntry tocEntry = new TocEntry();
                    tocEntry.Title = "Page " + i;
                    tocEntry.PageNumber = i;
                    tocEntries.Add(tocEntry);

                    // Add page number to TOC page
                    canvas = stamper.GetUnderContent(i);
                    ColumnText.ShowTextAligned(canvas, Element.ALIGN_LEFT, new Phrase("Page " + i), 36, 770, 0);
                }

                // Add TOC entries to the TOC page
                foreach (var entry in tocEntries)
                {
                    PdfOutline root = stamper.Writer.RootOutline;
                    PdfOutline tocOutline = new PdfOutline(root, new PdfDestination(PdfDestination.FITH), entry.Title);
                    stamper.Writer.SetOutlines(root);
                }
            }
        }

        // Close the PdfReader
        reader.Close();
    }
    catch (Exception ex)
    {
        // Handle any exceptions
        lblMessage.Text = "An error occurred while generating PDF with bookmarks and TOC: " + ex.Message;
    }
}



private void GeneratePdfWithBookmarkAndTOC(string mergedPdfPath, string outputPath)
{
    try
    {
        // Create a PdfReader instance to read the merged PDF
        PdfReader reader = new PdfReader(mergedPdfPath);

        // Create a PdfStamper instance to write modifications to the PDF
        using (FileStream outputStream = new FileStream(outputPath, FileMode.Create))
        {
            using (PdfStamper stamper = new PdfStamper(reader, outputStream))
            {
                // Initialize variables for bookmark and TOC generation
                int totalPages = reader.NumberOfPages;
                PdfContentByte canvas;

                // Create a list to hold TOC entries
                List<TocEntry> tocEntries = new List<TocEntry>();

                // Iterate through pages of the merged PDF
                for (int i = 1; i <= totalPages; i++)
                {
                    // Add a bookmark for each page
                    PdfOutline root = stamper.Writer.Outlines;
                    PdfDestination destination = new PdfDestination(PdfDestination.FITH);
                    PdfOutline outline = new PdfOutline(root, destination, "Page " + i);
                    stamper.Writer.Outlines = root;

                    // Create TOC entry
                    TocEntry tocEntry = new TocEntry();
                    tocEntry.Title = "Page " + i;
                    tocEntry.PageNumber = i;
                    tocEntries.Add(tocEntry);

                    // Add page number to TOC page
                    canvas = stamper.GetOverContent(i);
                    ColumnText.ShowTextAligned(canvas, Element.ALIGN_LEFT, new Phrase("Page " + i), 36, 770, 0);
                }

                // Add TOC entries to the TOC page
                foreach (var entry in tocEntries)
                {
                    PdfOutline root = stamper.Writer.Outlines;
                    PdfOutline tocOutline = new PdfOutline(root, new PdfDestination(PdfDestination.FITH), entry.Title);
                    stamper.Writer.Outlines = root;
                }
            }
        }

        // Close the PdfReader
        reader.Close();
    }
    catch (Exception ex)
    {
        // Handle any exceptions
        lblMessage.Text = "An error occurred while generating PDF with bookmarks and TOC: " + ex.Message;
    }
}
