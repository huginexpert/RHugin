\name{get.table}
\alias{get.table}

\title{Get Table}

\description{
Get the conditional probability table (CPT), experience table or fading table associated with a node in an RHugin domain.
}

\usage{
get.table(domain, node, type = c("cpt", "experience", "fading"),
          class = c("data.frame", "table", "ftable", "numeric"))
}

\arguments{
  \item{domain}{an RHugin domain.}
  \item{node}{a character string specifying the name of a node in \code{domain}.}
  \item{type}{a character string specifying the type of table.}
  \item{class}{a character string specifying the class of the returned table.}
}

\details{
Not all nodes have an experience or fading table by default (however, all nodes do have a conditional probability table).  When this function is used to get an experience or fading table from a node that doesn't have one, the appropriate table is created and returned.  Subsequent calls to this function will then return this already existing experience or fading table.  Experience and fading tables can be removed from a node using the \code{\link{delete.table}} function.
}

\value{
Depending on the value of the \code{class} argument either (1, default) a data frame, (2) a table, (3) a flat table (formatted to look like the tables in the Hugin GUI) or (4) a numeric vector (see the HUGIN API Reference Manual for interpretation).  When \code{classes = "data.frame"} (the default) the classes of the columns in the data frame are determined by the subtype of the associated node: a labeled node corresponds to a factor with levels equal to the states of the node, a numbered node corresponds to a numeric vector, a boolean node corresponds to a logical vector and an interval node corresponds to a factor with levels equal to the intervals of the node.  Additionally, the final column of the data frame contains the table data.  The table data column is named \code{"Freq"} for discrete chance nodes, \code{"Value"} for continuous nodes, \code{"Utility"} for utility nodes, \code{"Cost"} for decision nodes, \code{"Counts"} for experience tables and \code{"HMMM"} for fading tables.
}

\references{
HUGIN API Reference Manual \url{http://download.hugin.com/webdocs/manuals/api-manual.pdf}: \code{h_node_get_table}, \code{h_node_get_experience_table}, \code{h_node_get_fading_table}, \code{h_table_get_data}, \code{h_node_get_alpha}, \code{h_node_get_beta} and \code{h_node_get_gamma}.
}

\author{Kjell Konis \email{kjell.konis@icloud.com}}

\seealso{
  \code{\link{delete.table}}.
}

\examples{
demo("apple", echo = FALSE)

# Get the CPT of the node "Loses"
get.table(apple, "Loses")
}

\keyword{programming}


