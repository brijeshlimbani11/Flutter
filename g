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
