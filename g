private void ConvertHtmlToPdf()
{
    // Path to the HTML file
    string htmlFilePath = Server.MapPath("~/YourHtmlFile.html");

    // Path to the PDF file to be generated
    string pdfFilePath = Server.MapPath("~/YourGeneratedPdfFile.pdf");

    // Create a document
    Document document = new Document();

    try
    {
        // Initialize PDF writer
        PdfWriter writer = PdfWriter.GetInstance(document, new FileStream(pdfFilePath, FileMode.Create));

        // Open the document
        document.Open();

        // Read the HTML file
        using (TextReader reader = new StreamReader(htmlFilePath))
        {
            // Parse HTML and add it to the document
            HTMLWorker worker = new HTMLWorker(document);
            worker.Parse(reader);
        }

        // Add Table of Contents
        AddTableOfContents(document);
    }
    catch (Exception ex)
    {
        // Handle any exceptions
        Console.WriteLine("An error occurred: " + ex.Message);
    }
    finally
    {
        // Close the document
        document.Close();
    }
}








Server Error in '/' Application.
The document has no pages.
Description: An unhandled exception occurred during the execution of the current web request. Please review the stack trace for more information about the error and where it originated in the code.

Exception Details: System.IO.IOException: The document has no pages.

Source Error:


Line 59:             {
Line 60:                 // Close the document
Line 61:                 document.Close();
Line 62:             }
Line 63:         }

Source File: c:\users\sspl1366\documents\visual studio 2015\Projects\practice6\practice6\PDFMerge.aspx.cs    Line: 61

Stack Trace:










using System;
using System.IO;
using iTextSharp.text;
using iTextSharp.text.pdf;
using iTextSharp.text.html.simpleparser;

public partial class _Default : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {
        // Convert HTML to PDF
        ConvertHtmlToPdf();
    }

    private void ConvertHtmlToPdf()
    {
        // Path to the HTML file
        string htmlFilePath = Server.MapPath("~/YourHtmlFile.html");

        // Path to the PDF file to be generated
        string pdfFilePath = Server.MapPath("~/YourGeneratedPdfFile.pdf");

        // Create a document
        Document document = new Document();

        try
        {
            // Initialize PDF writer
            PdfWriter.GetInstance(document, new FileStream(pdfFilePath, FileMode.Create));

            // Open the document
            document.Open();

            // Read the HTML file
            using (TextReader reader = new StreamReader(htmlFilePath))
            {
                // Parse HTML and add it to the document
                HTMLWorker worker = new HTMLWorker(document);
                worker.Parse(reader);
            }

            // Add Table of Contents
            AddTableOfContents(document);
        }
        catch (Exception ex)
        {
            // Handle any exceptions
            Console.WriteLine("An error occurred: " + ex.Message);
        }
        finally
        {
            // Close the document
            document.Close();
        }
    }

    private void AddTableOfContents(Document document)
    {
        // Add a new page for the Table of Contents
        document.NewPage();

        // Add Table of Contents title
        Paragraph tocTitle = new Paragraph("Table of Contents", new Font(Font.FontFamily.HELVETICA, 16, Font.BOLD));
        document.Add(tocTitle);

        // Add TOC entries
        for (int i = 1; i <= document.PageSize.Height; i += 10)
        {
            Chunk chunk = new Chunk("Page " + i);
            chunk.SetAction(new PdfAction(i));
            Paragraph pageLink = new Paragraph(chunk);
            document.Add(pageLink);
        }
    }
}







<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>School Management System</title>
</head>
<body>
    <h1>School Management System</h1>
    
    <h2>Student Information</h2>
    <p>Name: John Doe</p>
    <p>Class: 10th Grade</p>
    <p>Roll No: 123</p>
    
    <h2>Teacher Information</h2>
    <p>Name: Jane Smith</p>
    <p>Subject: Mathematics</p>
    
    <h2>Class Schedule</h2>
    <table border="1">
        <tr>
            <th>Time</th>
            <th>Monday</th>
            <th>Tuesday</th>
            <th>Wednesday</th>
            <th>Thursday</th>
            <th>Friday</th>
        </tr>
        <tr>
            <td>8:00 AM - 9:00 AM</td>
            <td>Math</td>
            <td>Science</td>
            <td>English</td>
            <td>History</td>
            <td>Physical Education</td>
        </tr>
        <tr>
            <td>9:00 AM - 10:00 AM</td>
            <td>Science</td>
            <td>English</td>
            <td>History</td>
            <td>Physical Education</td>
            <td>Math</td>
        </tr>
        <!-- Add more rows for other time slots -->
    </table>
    
    <h2>Extracurricular Activities</h2>
    <ul>
        <li>Football Practice - Every Monday and Wednesday, 3:00 PM - 5:00 PM</li>
        <li>Chess Club - Every Friday, 2:00 PM - 4:00 PM</li>
    </ul>
    
    <h2>Library Information</h2>
    <p>The library is open from Monday to Friday, 9:00 AM to 5:00 PM.</p>
    
    <h2>Upcoming Events</h2>
    <p>1. Annual Sports Day - Date: March 15, 2024</p>
    <p>2. Science Fair - Date: April 20, 2024</p>
</body>
</html>











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

        // Set response headers to trigger download
        Response.Clear();
        Response.ContentType = "application/pdf";
        Response.AddHeader("content-disposition", "attachment; filename=output.pdf");

        // Write the merged PDF file to the response output stream
        Response.WriteFile(mergedPdfPath);
        Response.Flush();

        // End the response
        Response.End();

        // Display success message
        lblMessage.Text = "PDF files merged successfully. Merged PDF is being downloaded.";
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

        // Save the merged PDF to the file manager output
        string outputFileName = Server.MapPath("~/Output/output.pdf");
        File.Copy(mergedPdfPath, outputFileName, true);

        // Display success message
        lblMessage.Text = "PDF files merged successfully. Merged PDF saved to the file manager output.";
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

<form id="form1" runat="server">
    <div id="drop_zone" ondrop="dropHandler(event)" ondragover="dragOverHandler(event)">
        <p>Drag & drop PDF files here</p>
        <p>or</p>
        <label for="file_input">Click here to select files</label>
        <input type="file" id="file_input" multiple onchange="handleFiles(this.files)">
    </div>

    <!-- Use an HTML button for client-side action -->
    <button id="merge_btn_html" onclick="mergePDFs()">Merge PDFs (Client-side)</button>

    <!-- Use an ASP.NET button for server-side action -->
    <asp:Button ID="merge_btn_asp" runat="server" Text="Merge PDFs (Server-side)" OnClick="merge_btn_Click" />
    <asp:Label ID="lblMessage" runat="server" Text=""></asp:Label>

    <div id="upload_info"></div>
</form>

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
        // Implement client-side logic to merge PDFs
        alert('Merging PDFs (Client-side)...');
    }
</script>

</body>
</html>









Server Error in '/' Application.
Control 'Button1' of type 'Button' must be placed inside a form tag with runat=server.
Description: An unhandled exception occurred during the execution of the current web request. Please review the stack trace for more information about the error and where it originated in the code.

Exception Details: System.Web.HttpException: Control 'Button1' of type 'Button' must be placed inside a form tag with runat=server.

Source Error:

An unhandled exception was generated during the execution of the current web request. Information regarding the origin and location of the exception can be identified using the exception stack trace below.

Stack Trace:


[HttpException (0x80004005): Control 'Button1' of type 'Button' must be placed inside a form tag with runat=server.]
   System.Web.UI.Page.VerifyRenderingInServerForm(Control control) +9767915
   System.Web.UI.WebControls.Button.AddAttributesToRender(HtmlTextWriter writer) +59
   System.Web.UI.WebControls.WebControl.RenderBeginTag(HtmlTextWriter writer) +20
   System.Web.UI.WebControls.WebControl.Render(HtmlTextWriter writer) +20
   System.Web.UI.Control.RenderControlInternal(HtmlTextWriter writer, ControlAdapter adapter) +67
   System.Web.UI.Control.RenderControl(HtmlTextWriter writer, ControlAdapter adapter) +101
   System.Web.UI.Control.RenderControl(HtmlTextWriter writer) +27
   System.Web.UI.Control.RenderChildrenInternal(HtmlTextWriter writer, ICollection children) +129
   System.Web.UI.Control.RenderChildren(HtmlTextWriter writer) +14
   System.Web.UI.Page.Render(HtmlTextWriter writer) +30
   System.Web.UI.Control.RenderControlInternal(HtmlTextWriter writer, ControlAdapter adapter) +67
   System.Web.UI.Control.RenderControl(HtmlTextWriter writer, ControlAdapter adapter) +101
   System.Web.UI.Control.RenderControl(HtmlTextWriter writer) +27
   System.Web.UI.Page.ProcessRequestMain(Boolean includeStagesBeforeAsyncPoint, Boolean includeStagesAfterAsyncPoint) +1342

















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

                // Get the root outline
                PdfOutline root = stamper.Writer.DirectContent.RootOutline;

                // Iterate through pages of the merged PDF
                for (int i = 1; i <= totalPages; i++)
                {
                    // Add a bookmark for each page
                    PdfDestination destination = new PdfDestination(PdfDestination.FITH);
                    PdfOutline outline = new PdfOutline(root, destination, "Page " + i);

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
                    PdfOutline tocOutline = new PdfOutline(root, new PdfDestination(PdfDestination.FITH), entry.Title);
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
                    PdfDestination destination = new PdfDestination(PdfDestination.FITH);
                    PdfOutline outline = new PdfOutline(stamper.Writer, destination, "Page " + i);

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
                    PdfOutline tocOutline = new PdfOutline(stamper.Writer, new PdfDestination(PdfDestination.FITH), entry.Title);
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
