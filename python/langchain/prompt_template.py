from langchain.llms import OpenAI 
from langchain import PromptTemplate
from dotenv import load_dotenv
import os

load_dotenv()
api_key = os.getenv("OPENAI_API_KEY")
llm = OpenAI(model_name="text-davinci-003", openai_api_key=api_key)

template = """
I really want to travel to {location}. What should I do there?
Respond in one short sentence
"""

prompt = PromptTemplate(
    input_variables=["location"],
    template=template,
)

final_prompt = prompt.format(location='Rome')

print(f"Final Prompt: {final_prompt}")
print("----------")
print(f"LLM Output: {llm(final_prompt)}")