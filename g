
using iText.Kernel.Pdf;
using iText.Kernel.Utils;

namespace PDFMerge
{
    public class PDFMerge
    {
        private static string FILE1 = "/uploads/first.pdf";
        private static string FILE2 = "/uploads/second.pdf";
        private static string OUTPUT_FOLDER = "/myfiles/";
        
        static void Main(string[] args)
        {
            PdfDocument pdfDocument = new PdfDocument(new PdfReader(FILE1), new PdfWriter(OUTPUT_FOLDER + "merged.pdf"));
            PdfDocument pdfDocument2 = new PdfDocument(new PdfReader(FILE2));
            
            PdfMerger merger = new PdfMerger(pdfDocument);
            merger.Merge(pdfDocument2, 1, pdfDocument2.GetNumberOfPages());
            
            pdfDocument2.Close();
            pdfDocument.Close();
        }
    }
}
