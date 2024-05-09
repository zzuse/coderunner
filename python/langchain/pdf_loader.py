"""Module providing a docloader."""
from langchain.document_loaders import UnstructuredPDFLoader, OnlinePDFLoader
from langchain.text_splitter import RecursiveCharacterTextSplitter
from langchain.vectorstores import FAISS
from langchain.embeddings import OpenAIEmbeddings

loader = UnstructuredPDFLoader("./resume.pdf")
data = loader.load()
print(f"Found {len(data)} comments")
print(f"There are {len(data[0].page_content)} characters in your document")
