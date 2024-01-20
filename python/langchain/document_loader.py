"""Module providing a docloader."""
import os
from dotenv import load_dotenv
from langchain.document_loaders import HNLoader, TextLoader
from langchain.text_splitter import RecursiveCharacterTextSplitter
from langchain.vectorstores import FAISS
from langchain.embeddings import OpenAIEmbeddings

loader = HNLoader("https://news.ycombinator.com/item?id=34422627")
data = loader.load()
print(f"Found {len(data)} comments")
print(f"Here's a sample:\n\n{''.join([x.page_content[:150] for x in data[:2]])}")

#Download txt from https://paulgraham.com/worked.html
with open('./worked.txt', encoding="utf-8") as f:
    pg_work = f.read()
print(f"You have {len([pg_work])} document")

text_splitter = RecursiveCharacterTextSplitter(
    chunk_size = 150,
    chunk_overlap = 20,
)

texts = text_splitter.create_documents([pg_work])
print(f"You have {len(texts)} documents")
print("Preview:")
print(texts[0].page_content, "\n")
print(texts[1].page_content)

textloader = TextLoader('./worked.txt')
documents = textloader.load()
text_splitter = RecursiveCharacterTextSplitter(chunk_size=1000, chunk_overlap=50)
texts = text_splitter.split_documents(documents)

load_dotenv()
api_key = os.getenv("OPENAI_API_KEY")
embeddings = OpenAIEmbeddings(openai_api_key=api_key)
db = FAISS.from_documents(texts, embeddings)

retriever = db.as_retriever()
docs = retriever.get_relevant_documents('What types of things did the author want to build?')

print("\n\n".join([x.page_content[:200] for x in docs[:2]]))
